/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date August 20 2024
 * @version v0.1.0
 * @brief This file contains the definitions of the methods of the class Kyber
 */

#include "Kyber.h"
#include "../../.conf/constants_values.h"

/**
 * @brief Construct a new Kyber:: Kyber object
 * 
 * @param option : The option to choose the parameters of the Kyber cryptosystem
 */
Kyber::Kyber(int option, const std::vector<int>& seed) {
  KyberConstants::InitializeConstants(option);
  n_ = KyberConstants::N;
  q_ = KyberConstants::Q;
  k_ = KyberConstants::K;
  n1_ = KyberConstants::N1;
  n2_ = KyberConstants::N2;
  du_ = KyberConstants::Du;
  dv_ = KyberConstants::Dv;  
  ntt_ = std::make_unique<NTT>(NTT(n_, q_));
  keccak_ = std::make_unique<Keccak>(Keccak());
  pwm_unit_ = std::make_unique<PWMUnit>(PWMUnit(n_, q_));
  encdec_unit_ = std::make_unique<EncDecUnit>(EncDecUnit(q_));
  sampling_unit_ = std::make_unique<SamplingUnit>(SamplingUnit(k_, n_));
  compressor_unit_ = std::make_unique<CompressorUnit>(CompressorUnit(q_));
  seed_ = seed;
}


/**
 * @brief Generate a key pair
 * 
 * @return std::pair<Bytes, Bytes> : The generated key pair
 */
std::pair<Bytes, Bytes> Kyber::KeyGen() {
  Bytes seed = GenerateSeed_(KyberConstants::SeedSize);
  if (seed_.size() > 0) {
    seed = Bytes(seed_);
  }
  std::vector<Bytes> rho_sigma = GenerateRhoSigma_(seed);
  Bytes rho = rho_sigma[0];
  Bytes sigma = rho_sigma[1];
  Matrix<Polynomial<int>> a = ntt_->GenerateMatrix_(k_, rho, true);
  int N = 0;
  std::pair<Matrix<Polynomial<int>>, int> pair_secret = sampling_unit_->GenerateDistribuitionMatrix(sigma, n1_, N);
  N = pair_secret.second;
  Matrix<Polynomial<int>> s = pair_secret.first;
  // std::cout << s << std::endl;
  Matrix<Polynomial<int>> s_ntt = applyNTTMatrix_(s, k_);
  // std::cout << s_ntt << std::endl;
  std::pair<Matrix<Polynomial<int>>, int> pair_error = sampling_unit_->GenerateDistribuitionMatrix(sigma, n1_, N);
  N = pair_error.second;
  Matrix<Polynomial<int>> e = pair_error.first;  
  // std::cout << e << std::endl;
  Matrix<Polynomial<int>> e_ntt = applyNTTMatrix_(e, k_);
  // std::cout << e_ntt << std::endl;
  Matrix<Polynomial<int>> A_s = pwm_unit_->multMatrixViaNTT(a, s_ntt);
  // std::cout << A_s << std::endl;
  Matrix<Polynomial<int>> t = A_s + e_ntt;
  // std::cout << t << std::endl;
  Bytes t_encoded = encdec_unit_->EncodeMatrixToBytes(t, 12) + rho;
  // std::cout << t_encoded.FromBytesToHex() << std::endl;
  Bytes s_encoded = encdec_unit_->EncodeMatrixToBytes(s_ntt, 12);
  // std::cout << s_encoded.FromBytesToHex() << std::endl;
  pk_ = std::make_unique<Bytes>(t_encoded);
  sk_ = std::make_unique<Bytes>(s_encoded);
  return std::make_pair(t_encoded, s_encoded);
}


/**
 * @brief Apply the NTT to a matrix
 * 
 * @param matrix : The matrix to apply the NTT
 * @param k : The number of rows of the matrix
 * @return Matrix<Polynomial<int>> : The matrix with the NTT applied
 */
Matrix<Polynomial<int>> Kyber::applyNTTMatrix_(const Matrix<Polynomial<int>>& matrix, int k) const {
  Matrix<Polynomial<int>> matrix_ntt = Matrix<Polynomial<int>>(k, 1, n_);
  for (int i = 0; i < k; ++i) {
    matrix_ntt(i, 0) = ntt_->NTT_Kyber(matrix(i, 0), true);
  }
  return matrix_ntt;
}



/**
 * @brief Generate a seed of a given size
 * 
 * @param seed_size : The size of the seed
 * @return Bytes : The generated seed
 */
Bytes Kyber::GenerateSeed_(int seed_size) const {
  std::vector<unsigned char> seed(seed_size);
  std::srand(std::time(nullptr));
  std::generate(seed.begin(), seed.end(), []() {
    return rand() % 256;
  });
  return Bytes(seed);
}

/**
 * @brief Generate the rho and sigma values
 * 
 * @param seed : The seed to generate the rho and sigma values
 * @return std::vector<Bytes> : The generated rho and sigma values
 */
std::vector<Bytes> Kyber::GenerateRhoSigma_(const Bytes& seed) const {
  return keccak_->G(seed);
}
