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
  encdec_unit_ = std::make_unique<EncDecUnit>(EncDecUnit(n_));
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
 * @brief Encrypt a message
 * 
 * @param pk : The public key
 * @param message : The message to encrypt
 * @param seed : The seed to generate the rho and sigma values
 * @param n1 : The n1 value
 * @param n2 : The n2 value
 * @param du : The du value
 * @param dv : The dv value
 * @return Bytes : The encrypted message
 */
Bytes Kyber::Encryption(const Bytes& pk, const Bytes& message, const Bytes& seed, int k, int n1, int n2, int du, int dv) {
  Bytes rho = pk.GetNBytes(pk.GetBytesSize() - 32, 32);
  Matrix<Polynomial<int>> t_matrix = encdec_unit_->DecodeBytesToMatrix(pk, 1, k_, 12);
  Polynomial<int> m_pol = compressor_unit_->Decompress_(encdec_unit_->decode_(message, 1), 1);
  
  int N = 0;  
  Matrix<Polynomial<int>> At = ntt_->GenerateMatrix_(k_, rho, false);
  std::pair<Matrix<Polynomial<int>>, int> pair_r = sampling_unit_->GenerateDistribuitionMatrix(seed, n1, N);
  Matrix<Polynomial<int>> r = pair_r.first;
  Matrix<Polynomial<int>> r_ntt = applyNTTMatrix_(r, k_);
  std::pair<Matrix<Polynomial<int>>, int> pair_error1 = sampling_unit_->GenerateDistribuitionMatrix(seed, n2, pair_r.second);
  Matrix<Polynomial<int>> e1 = pair_error1.first;
  Polynomial<int> e2 = sampling_unit_->_CBD(keccak_->PRF(seed, pair_error1.second, 64 * n2), n2);

  Matrix<Polynomial<int>> A_r = pwm_unit_->multMatrixViaNTT(At, r_ntt);
  Matrix<Polynomial<int>> A_r_ntt = applyNTTMatrix_(A_r, k_, false);
  Matrix<Polynomial<int>> u = A_r_ntt + e1;

  Polynomial<int> v = pwm_unit_->multMatrixViaNTT(t_matrix, r_ntt)(0, 0);
  Polynomial<int> v_ntt = ntt_->NTT_Kyber(v, false);
  v_ntt = v_ntt + e2;
  v_ntt = v_ntt + m_pol;
  Bytes c1 = encdec_unit_->EncodeMatrixToBytes(compressor_unit_->CompressMatrix(u, du), du);
  Bytes c2 = encdec_unit_->encode_(compressor_unit_->Compress_(v_ntt, dv), dv);
  Bytes c_encoded = c1 + c2;
  return c_encoded;
}

/**
 * @brief Decrypt a message
 * 
 * @param sk : The secret key
 * @param ciphertext : The ciphertext to decrypt
 * @param k : The k value
 * @param du : The du value
 * @param dv : The dv value
 * @return Bytes : The decrypted message
 */
Bytes Kyber::Decryption(const Bytes& sk, const Bytes& ciphertext, int k, int du, int dv) {
  Bytes c2 = ciphertext.GetNBytes(du * k * int(n_ / 8), ciphertext.GetBytesSize() - du * k * int(n_ / 8));
  Matrix<Polynomial<int>> u = compressor_unit_->DecompressMatrix(encdec_unit_->DecodeBytesToMatrix(ciphertext, k, 1, du), du);
  Matrix<Polynomial<int>> u_ntt = applyNTTMatrix_(u, k, true);

  Polynomial<int> v = compressor_unit_->Decompress_(encdec_unit_->decode_(c2, dv), dv);
  Matrix<Polynomial<int>> st = encdec_unit_->DecodeBytesToMatrix(sk, 1, k, 12); 
  Polynomial<int> st_u = pwm_unit_->multMatrixViaNTT(st, u_ntt)(0, 0);
  Polynomial<int> st_u_ntt = ntt_->NTT_Kyber(st_u, false);
  Polynomial<int> m = v - st_u_ntt;
  return encdec_unit_->encode_(compressor_unit_->Compress_(m, 1), 1);
}

/**
 * @brief Generate a key pair for the KEM
 * 
 * @return std::pair<Bytes, Bytes> : The generated key pair
 */
std::pair<Bytes, Bytes> Kyber::KEMKeyGen() {
  Bytes seed = GenerateSeed_(KyberConstants::SeedSize);
  std::pair<Bytes, Bytes> key_pair = KeyGen();
  Bytes pk = key_pair.first;
  Bytes sk = key_pair.second + pk + keccak_->H(pk, 32) + seed;
  return std::pair<Bytes, Bytes>{pk, sk};
}


/**
 * @brief Encapsulate a key
 * 
 * @param pk : The public key
 * @param seed : The seed to generate the rho and sigma values
 * @param k : The k value
 * @param n1 : The n1 value
 * @param n2 : The n2 value
 * @param du : The du value
 * @param dv : The dv value
 * @return std::pair<Bytes, Bytes> : The encapsulated key
 */
std::pair<Bytes, Bytes> Kyber::KEMEncapsulation(const Bytes& pk, int k, int n1, int n2, int du, int dv) {
  Bytes message = Keccak::H(GenerateSeed_(KyberConstants::SeedSize), 32);
  std::vector<Bytes> pair = keccak_->G(message + keccak_->H(pk, 32));
  Bytes K_prime = pair[0];
  Bytes r = pair[1];
  Bytes c = Encryption(pk, message, r, k, n1, n2, du, dv);
  Bytes K = keccak_->KDF(K_prime + keccak_->H(c, 32), 32);
  return std::pair<Bytes, Bytes>{c, K};
}


/**
 * @brief Decapsulate a key
 * 
 * @param sk : The secret key
 * @param ciphertext : The ciphertext to decapsulate
 * @param k : The k value
 * @param n1 : The n1 value
 * @param n2 : The n2 value
 * @param du : The du value
 * @param dv : The dv value
 * @return Bytes : The decapsulated key
 */
Bytes Kyber::KEMDecapsulation(const Bytes& sk, const Bytes& ciphertext, int k, int n1, int n2, int du, int dv) {
  if (sk.GetBytesSize() != (24 * k * int(n_ / 8) + 96)) {
    throw std::invalid_argument("The secret key is not the correct size");
  }
  if (ciphertext.GetBytesSize() != (du * k * int(n_ / 8) + dv * int(n_ / 8))) {
    throw std::invalid_argument("The cyphered text is not the correct size");
  }
  int entry_index = 12 * k * int(n_ / 8);
  int following_index = 24 * k * int(n_ / 8);
  Bytes pk = sk.GetNBytes(entry_index, KyberConstants::PkSize);
  Bytes h = sk.GetNBytes(following_index + 32, 32);
  Bytes z = sk.GetNBytes(following_index + 64, 32);
  // Decrypting the message
  Bytes m_prime = Decryption(sk, ciphertext, k, du, dv);
  // Generating the K' and r' values
  std::vector<Bytes> pair = keccak_->G(m_prime + h);
  Bytes K_prime = pair[0];
  Bytes r_prime = pair[1];
  // Encrypting the message again
  Bytes c_prime = Encryption(pk, m_prime, r_prime, k, n1, n2, du, dv);
  return keccak_->KDF((c_prime == ciphertext ? K_prime : z) + keccak_->H(c_prime, 32), 32);
}


/**
 * @brief Apply the NTT to a matrix
 * 
 * @param matrix : The matrix to apply the NTT
 * @param k : The number of rows of the matrix
 * @return Matrix<Polynomial<int>> : The matrix with the NTT applied
 */
Matrix<Polynomial<int>> Kyber::applyNTTMatrix_(const Matrix<Polynomial<int>>& matrix, int k, bool is_ntt) const {
  Matrix<Polynomial<int>> matrix_ntt = Matrix<Polynomial<int>>(k, 1, n_);
  for (int i = 0; i < k; ++i) {
    matrix_ntt(i, 0) = ntt_->NTT_Kyber(matrix(i, 0), is_ntt);
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
