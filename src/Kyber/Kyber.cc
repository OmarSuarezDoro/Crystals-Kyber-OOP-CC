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

/**
 * @brief Construct a new Kyber:: Kyber object
 * 
 * @param option : The option to choose the parameters of the Kyber cryptosystem
 */
Kyber::Kyber(int option, const std::vector<int>& seed) {
  InitializeConstants(option);
  n_ = KyberConstants::N;
  q_ = KyberConstants::Q;
  k_ = KyberConstants::K;
  n1_ = KyberConstants::N1;
  n2_ = KyberConstants::N2;
  du_ = KyberConstants::Du;
  dv_ = KyberConstants::Dv;  
  seed_ = seed;
  ntt_ = std::make_unique<NTT>(NTT(n_, q_));
  encdec_unit_ = std::make_unique<EncDecUnit>(EncDecUnit(n_));
  sampling_unit_ = std::make_unique<SamplingUnit>(SamplingUnit(k_, n_));
  compressor_unit_ = std::make_unique<CompressorUnit>(CompressorUnit(q_));
}


/**
 * @brief Generate a key pair
 * 
 * @return std::pair<Bytes, Bytes> : The generated key pair
 */
std::pair<Bytes, Bytes> Kyber::KeyGen() {
  auto start = std::chrono::high_resolution_clock::now();
  Bytes seed = GenerateSeed_(KyberConstants::SeedSize);
  if (seed_.size() > 0) {
    seed = Bytes(seed_);
  }
  std::pair<Bytes, Bytes> rho_sigma = GenerateRhoSigma_(seed);
  Bytes rho = rho_sigma.first;
  Bytes sigma = rho_sigma.second;

  #ifdef DEBUG
    std::cout << "Seed Generated: " << seed.FromBytesToHex() << std::endl;
    std::cout << "Rho and Sigma values Generated:" << std::endl;
    std::cout << "Rho: " << rho.FromBytesToHex() << std::endl;
    std::cout << "Sigma: " << sigma.FromBytesToHex() << std::endl << std::endl;
  #endif

  Matrix<Polynomial<int>> a = ntt_->GenerateMatrix_(k_, rho, true);
  int N = 0;
  std::pair<Matrix<Polynomial<int>>, int> pair_secret = sampling_unit_->GenerateDistribuitionMatrix(sigma, n1_, N);
  N = pair_secret.second;
  Matrix<Polynomial<int>> s = pair_secret.first;
  Matrix<Polynomial<int>> s_ntt = applyNTTMatrix_(s, k_);
  std::pair<Matrix<Polynomial<int>>, int> pair_error = sampling_unit_->GenerateDistribuitionMatrix(sigma, n1_, N);
  N = pair_error.second;
  Matrix<Polynomial<int>> e = pair_error.first;  
  Matrix<Polynomial<int>> e_ntt = applyNTTMatrix_(e, k_);

  #ifdef DEBUG
    std::cout << "Matrix A: " << a << std::endl;
    std::cout << "Matrix S: " << s << std::endl;
    std::cout << "Matrix E: " << e << std::endl;
    std::cout << "Matrix S NTT: " << s_ntt << std::endl;
    std::cout << "Matrix E NTT: " << e_ntt << std::endl << std::endl;
  #endif


  Matrix<Polynomial<int>> A_s = ntt_->multMatrixViaNTT(a, s_ntt);
  Matrix<Polynomial<int>> t = A_s + e_ntt;

  #ifdef DEBUG
    std::cout << "Matrix A * S: " << A_s << std::endl;
    std::cout << "Matrix T: " << t << std::endl << std::endl;
  #endif
    
  Bytes t_encoded = encdec_unit_->EncodeMatrixToBytes(t, 12) + rho;
  Bytes s_encoded = encdec_unit_->EncodeMatrixToBytes(s_ntt, 12);

  #ifdef DEBUG
    std::cout << "Public Key: " << t_encoded.FromBytesToHex() << std::endl;
    std::cout << "Secret Key: " << s_encoded.FromBytesToHex() << std::endl << std::endl;
  #endif

  #ifdef TIME
    std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - start;
    time_results_["KeyGen"].push_back(elapsed.count());
  #endif
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
 * @return Bytes : The encrypted message
 */
Bytes Kyber::Encryption(const Bytes& pk, const Bytes& message, const Bytes& seed) {
  auto start = std::chrono::high_resolution_clock::now();
  Bytes rho = pk.GetNBytes(pk.GetBytesSize() - 32, 32);
  
  #ifdef DEBUG
    std::cout << "Rho: " << rho.FromBytesToHex() << std::endl;
  #endif
  
  Matrix<Polynomial<int>> t_matrix = encdec_unit_->DecodeBytesToMatrix(pk, 1, k_, 12);
  Polynomial<int> m_pol = compressor_unit_->Decompress_(encdec_unit_->Decode_(message, 1), 1);

  #ifdef DEBUG
    std::cout << "Matrix T: " << t_matrix << std::endl;
    std::cout << "Message: " << m_pol << std::endl << std::endl;
  #endif

  int N = 0;  
  Matrix<Polynomial<int>> At = ntt_->GenerateMatrix_(k_, rho, false);
  std::pair<Matrix<Polynomial<int>>, int> pair_r = sampling_unit_->GenerateDistribuitionMatrix(seed, n1_, N);
  
  #if DEBUG
    std::cout << "Matrix A Transposed: " << At << std::endl;
    std::cout << "Matrix R: " << pair_r.first << std::endl;
  #endif

  Matrix<Polynomial<int>> r = pair_r.first;
  Matrix<Polynomial<int>> r_ntt = applyNTTMatrix_(r, k_);
  std::pair<Matrix<Polynomial<int>>, int> pair_error1 = sampling_unit_->GenerateDistribuitionMatrix(seed, n2_, pair_r.second);
  Matrix<Polynomial<int>> e1 = pair_error1.first;
  Polynomial<int> e2 = sampling_unit_->CBD_(Keccak::PRF(seed, pair_error1.second, 64 * n2_), n2_);

  #ifdef DEBUG
    std::cout << "Matrix R NTT: " << r_ntt << std::endl;
    std::cout << "Matrix E1: " << e1 << std::endl;
    std::cout << "Polynomial E2: " << e2 << std::endl << std::endl;
  #endif

  Matrix<Polynomial<int>> A_r = ntt_->multMatrixViaNTT(At, r_ntt);
  Matrix<Polynomial<int>> A_r_ntt = applyNTTMatrix_(A_r, k_, false);
  Matrix<Polynomial<int>> u = A_r_ntt + e1;

  #ifdef DEBUG
    std::cout << "Matrix A Transposed * R: " << A_r << std::endl;
    std::cout << "Matrix U: " << u << std::endl << std::endl;
  #endif

  Polynomial<int> v = ntt_->multMatrixViaNTT(t_matrix, r_ntt)(0, 0);
  Polynomial<int> v_ntt = ntt_->NTT_Kyber(v, false);
  v_ntt = v_ntt + e2;
  v_ntt = v_ntt + m_pol;
  
  #ifdef DEBUG
    std::cout << "Polynomial V: " << v << std::endl;
    std::cout << "Polynomial V NTT: " << v_ntt << std::endl << std::endl;
  #endif

  Bytes c1 = encdec_unit_->EncodeMatrixToBytes(compressor_unit_->CompressMatrix(u, du_), du_);
  Bytes c2 = encdec_unit_->Encode_(compressor_unit_->Compress_(v_ntt, dv_), dv_);
  Bytes c_encoded = c1 + c2;

  #ifdef DEBUG
    std::cout << "C1: " << c1.FromBytesToHex() << std::endl;
    std::cout << "C2: " << c2.FromBytesToHex() << std::endl;
    std::cout << "Ciphertext: " << c_encoded.FromBytesToHex() << std::endl << std::endl;
  #endif

  #ifdef TIME
    std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - start;
    time_results_["Encryption"].push_back(elapsed.count());;	
  #endif

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
Bytes Kyber::Decryption(const Bytes& sk, const Bytes& ciphertext) {
  auto start = std::chrono::high_resolution_clock::now();
  Bytes c2 = ciphertext.GetNBytes(du_ * k_ * int(n_ / 8), ciphertext.GetBytesSize() - du_ * k_ * int(n_ / 8));
  Matrix<Polynomial<int>> u = compressor_unit_->DecompressMatrix(encdec_unit_->DecodeBytesToMatrix(ciphertext, k_, 1, du_), du_);
  Matrix<Polynomial<int>> u_ntt = applyNTTMatrix_(u, k_, true);

  #ifdef DEBUG
    std::cout << "c2: " << c2.FromBytesToHex() << std::endl;
    std::cout << "Matrix U: " << u << std::endl;
    std::cout << "Matrix U NTT: " << u_ntt << std::endl;
  #endif

  Polynomial<int> v = compressor_unit_->Decompress_(encdec_unit_->Decode_(c2, dv_), dv_);
  Matrix<Polynomial<int>> st = encdec_unit_->DecodeBytesToMatrix(sk, 1, k_, 12); 
  Polynomial<int> st_u = ntt_->multMatrixViaNTT(st, u_ntt)(0, 0);
  Polynomial<int> st_u_ntt = ntt_->NTT_Kyber(st_u, false);
  Polynomial<int> m = v - st_u_ntt;
  Bytes result = encdec_unit_->Encode_(compressor_unit_->Compress_(m, 1), 1);

  #ifdef DEBUG
    std::cout << "Polynomial V: " << v << std::endl;
    std::cout << "Polynomial ST * U: " << st_u << std::endl;
    std::cout << "Polynomial ST * U NTT: " << st_u_ntt << std::endl;
    std::cout << "Polynomial M: " << m << std::endl << std::endl;
  #endif

  #ifdef TIME
    std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - start;
    time_results_["Decryption"].push_back(elapsed.count());
  #endif

  return result;
}


/**
 * @brief Generate a key pair for the KEM
 * 
 * @return std::pair<Bytes, Bytes> : The generated key pair
 */
std::pair<Bytes, Bytes> Kyber::KEMKeyGen() {
  auto start = std::chrono::high_resolution_clock::now();
  Bytes seed = GenerateSeed_(KyberConstants::SeedSize);

  #ifdef DEBUG
    std::cout << "Seed Generated: " << seed.FromBytesToHex() << std::endl;
  #endif
  
  std::pair<Bytes, Bytes> key_pair = Kyber::KeyGen();
  Bytes pk = key_pair.first;
  Bytes sk = key_pair.second + pk + Keccak::H(pk, 32) + seed;
  
  #ifdef DEBUG
    std::cout << "Secret Key: " << sk.FromBytesToHex() << std::endl;
  #endif
  
  #ifdef TIME
    std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - start;
    time_results_["KEMKeyGen"].push_back(elapsed.count());
  #endif

  return std::pair<Bytes, Bytes>{pk, sk};
}


/**
 * @brief Encapsulate a key
 * 
 * @param pk : The public key
 * @return std::pair<Bytes, Bytes> : The encapsulated key
 */
std::pair<Bytes, Bytes> Kyber::KEMEncapsulation(const Bytes& pk) {
  auto start = std::chrono::high_resolution_clock::now();
  Bytes message = Keccak::H(GenerateSeed_(KyberConstants::SeedSize), KyberConstants::SeedSize);

  #ifdef DEBUG
    std::cout << "Message: " << message.FromBytesToHex() << std::endl;
  #endif

  std::pair<Bytes, Bytes> pair = Keccak::G(message + Keccak::H(pk, KyberConstants::SeedSize));

  #ifdef DEBUG
    std::cout << "K' and r': " << pair.first.FromBytesToHex() << " " << pair.second.FromBytesToHex() << std::endl;
  #endif
  Bytes K_prime = pair.first;
  Bytes r = pair.second;
  Bytes c = Encryption(pk, message, r);
  Bytes K = Keccak::KDF(K_prime + Keccak::H(c, KyberConstants::SeedSize), KyberConstants::SeedSize);

  #ifdef DEBUG
    std::cout << "Ciphertext: " << c.FromBytesToHex() << std::endl;
    std::cout << "K: " << K.FromBytesToHex() << std::endl << std::endl;
  #endif

  #ifdef TIME
    std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - start;
    time_results_["KEMEncapsulation"].push_back(elapsed.count());
  #endif

  return std::pair<Bytes, Bytes>{c, K};
}


/**
 * @brief Decapsulate a key
 * 
 * @param sk : The secret key
 * @param ciphertext : The ciphertext to decapsulate
 * @return Bytes : The decapsulated key
 */
Bytes Kyber::KEMDecapsulation(const Bytes& sk, const Bytes& ciphertext) {
  auto start = std::chrono::high_resolution_clock::now();
  if (sk.GetBytesSize() != (24 * k_ * int(n_ / 8) + 96)) {
    throw std::invalid_argument("The secret key is not the correct size");
  }
  if (ciphertext.GetBytesSize() != (du_ * k_ * int(n_ / 8) + dv_ * int(n_ / 8))) {
    throw std::invalid_argument("The cyphered text is not the correct size");
  }
  int entry_index = 12 * k_ * int(n_ / 8);
  int following_index = 24 * k_ * int(n_ / 8);
  Bytes pk = sk.GetNBytes(entry_index, KyberConstants::PkSize);
  Bytes h = sk.GetNBytes(following_index + 32, 32);
  Bytes z = sk.GetNBytes(following_index + 64, 32);

  #ifdef DEBUG
    std::cout << "Public Key: " << pk.FromBytesToHex() << std::endl;
    std::cout << "H: " << h.FromBytesToHex() << std::endl;
    std::cout << "Z: " << z.FromBytesToHex() << std::endl;
  #endif
  // Decrypting the message
  Bytes m_prime = Decryption(sk, ciphertext);
  // Generating the K' and r' values
  std::pair<Bytes, Bytes> pair = Keccak::G(m_prime + h);
  Bytes K_prime = pair.first;
  Bytes r_prime = pair.second;
  // Encrypting the message again
  Bytes c_prime = Encryption(pk, m_prime, r_prime);

  #ifdef DEBUG
    std::cout << "Message Decrypted: " << m_prime.FromBytesToHex() << std::endl;
    std::cout << "K' and r': " << K_prime.FromBytesToHex() << " " << r_prime.FromBytesToHex() << std::endl;
    std::cout << "Ciphertext: " << c_prime.FromBytesToHex() << std::endl;
  #endif
  Bytes result = Keccak::KDF((c_prime == ciphertext ? K_prime : z) + Keccak::H(c_prime, 32), 32);
  
  #ifdef TIME
    std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - start;
    time_results_["KEMDecapsulation"].push_back(elapsed.count());
  #endif
  
  return result;
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
  int n = int(n_);
  std::generate(seed.begin(), seed.end(), [n]() {
    return rand() % n;
  });
  return Bytes(seed);
}

/**
 * @brief Generate the rho and sigma values
 * 
 * @param seed : The seed to generate the rho and sigma values
 * @return std::pair<Bytes, Bytes> : The generated rho and sigma values
 */
std::pair<Bytes, Bytes> Kyber::GenerateRhoSigma_(const Bytes& seed) const {
  return Keccak::G(seed);
}

/**
 * @brief Initialize the constants of the Kyber cryptosystem
 * @param option : The option to choose the parameters of the Kyber cryptosystem
 */
void Kyber::InitializeConstants(int option) {
  switch (option) {
    case 512:
      KyberConstants::N = 256;
      KyberConstants::Q = 3329;
      KyberConstants::K = 2;
      KyberConstants::N1 = 3;
      KyberConstants::N2 = 2;
      KyberConstants::Du = 10;
      KyberConstants::Dv = 4;
      KyberConstants::PkSize = 800;
      KyberConstants::SkSize = 1632;
      KyberConstants::CtSize = 768;
      KyberConstants::SeedSize = 32;
      break;
    case 768:
      KyberConstants::N = 256;
      KyberConstants::Q = 3329;
      KyberConstants::K = 3;
      KyberConstants::N1 = 3;
      KyberConstants::N2 = 2;
      KyberConstants::Du = 10;
      KyberConstants::Dv = 4;
      KyberConstants::PkSize = 1184;
      KyberConstants::SkSize = 2400;
      KyberConstants::CtSize = 1088;
      break;
    case 1024:
      KyberConstants::N = 256;
      KyberConstants::Q = 3329;
      KyberConstants::K = 4;
      KyberConstants::N1 = 2;
      KyberConstants::N2 = 2;
      KyberConstants::Du = 11;
      KyberConstants::Dv = 5;
      KyberConstants::PkSize = 1568;
      KyberConstants::SkSize = 3168;
      KyberConstants::CtSize = 1568;
      break;
    default:
      break;
  }
}