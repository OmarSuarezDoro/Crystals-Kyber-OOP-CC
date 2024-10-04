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

KleptoKyber::KleptoKyber(int option, Bytes attacker_pk, const std::vector<int>& seed) : Kyber(option, seed) {
  attacker_pk_ = attacker_pk;
}

Bytes KleptoKyber::RunBackdoor() {
  // We use the public key of the attacker to encrypt the shared secret
  std::pair<Bytes, Bytes> pair_ct_sharedm = cypher_box->Encrypt(attacker_pk_); // 96 bytes = 768 bits  
  std::cout << "Ciphertext: " << pair_ct_sharedm.first.FromBytesToHex() << std::endl;
  Bytes seed_a = GenerateSeed_(KyberConstants::SeedSize);
  Bytes seed_b = pair_ct_sharedm.second;
  Matrix<Polynomial<int>> a = ntt_->GenerateMatrix_(k_, seed_a, true);
  int N = 0;
  std::pair<Matrix<Polynomial<int>>, int> pair_s_counter = sampling_unit_->GenerateDistribuitionMatrix(seed_b, n1_, N);
  // std::cout << "Matrix s: " << pair_s_counter.first << std::endl;
  Matrix<Polynomial<int>> s_ntt = applyNTTMatrix_(pair_s_counter.first, k_);
  std::pair<Matrix<Polynomial<int>>, int> pair_e_counter = sampling_unit_->GenerateDistribuitionMatrix(seed_b, n1_, pair_s_counter.second);
  Matrix<Polynomial<int>> e_ntt = applyNTTMatrix_(pair_e_counter.first, k_);
  // t = INTT(â ◦ NTT(s)) + e
  Matrix<Polynomial<int>> t = applyNTTMatrix_(ntt_->multMatrixViaNTT(a, s_ntt), k_, false) + e_ntt;
  // ctbd = (bt0 , bt1 , . . . , btb ); c = ⌈b/(k · n)⌉
  int b = pair_ct_sharedm.first.GetBytesSize() * BYTE_SIZE;
  int c = b / (k_ * n_) + 1;
  // Initialize the polynomial p with c length - NOT SURE ABOUT THIS!!  
  Polynomial<int> p(k_ * n_);
  int size_p_without_zeros = b / c;
  // Pack the bits of the ciphertext into the polynomial p
  for (int i = 0; i < size_p_without_zeros; ++i) {
    p[i] = 0;
    for (int j = i * c; j < (i + 1) * c; ++j) { // TODO: need to know if we need to include the last bit or not
      // Extract the bit from the corresponding position of the ciphertext
      int bit_j = pair_ct_sharedm.first.GetBit(j);
      // Pack this bit into the coefficient p[i] using bit shifting.
      p[i] += bit_j * (1 << (j - i * c));
    }
  }
  Polynomial<int> h(p.GetSize());  
  // Transform the matrix t into a polynomial to calculate the compensation polynomial
  Polynomial<int> t_polynomial = t.GetPolynomialFromMatrix(n_);
  // Compute the compensation polynomial
    // h[i] = std::abs((p[i] - t_polynomial[i]) % (2 << c - 1)) ;
  for (int i = 0; i < p.GetSize(); ++i) {
    h[i] = (p[i] - t_polynomial[i])  % (2 << c - 1);
  }
  // std::cout << "Polynomial h: " << h << std::endl << std::endl;
  Polynomial<int> t_prime = t_polynomial + h;
  // std::cout << t_prime << std::endl;
  
  Polynomial<int> copy = t_prime;
  for (int i = 0; i < copy.GetSize(); ++i) {
    copy[i] = copy[i] % (2 << c - 1);
  } 
  // std::cout << copy << std::endl;
  if (copy == p) {
    std::cout << "SIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII" << std::endl;
  }
  Matrix<Polynomial<int>> t_prime_matrix(k_, 1);
  int current_row = 0;

  for (int i = 0; i < t_prime.GetSize(); i += n_) {
    t_prime_matrix(current_row, 0) = ntt_->NTT_Kyber(t_prime.GetSubPolynomial(i, i + n_), true);
    current_row++;
  }
  return seed_a + encdec_unit_->EncodeMatrixToBytes(t_prime_matrix, 12);
}


void KleptoKyber::recoverSecretKey(const Bytes& pk) {
  Bytes seed_a = pk.GetNBytes(0, 32);
  Bytes t_prime_bytes = pk.GetNBytes(32, pk.GetBytesSize() - 32);
  // Recover t'
  Matrix<Polynomial<int>> t_prime = encdec_unit_->DecodeBytesToMatrix(t_prime_bytes, k_, 1, 12);
  // Apply the inverse NTT to t'
  t_prime = applyNTTMatrix_(t_prime, k_, false); 

  int b = KyberConstants::CtSize; // Number of cyphertext bits
  int c = b / (k_ * n_) + 1; // Number of bits per coefficient
  Polynomial<int> t_prime_polynomial = t_prime.GetPolynomialFromMatrix(n_);

  // std::cout << "b: " << b << std::endl;
  // std::cout << "c: " << c << std::endl;
  // std::cout << "size_of_p_without_zeros: " << size_of_p_without_zeros << std::endl;

  // Reconstruir el polinomio p a partir de t_prime
  int size_of_p_without_zeros = b / c + 1; // Number of coefficients in p without appended zeros
  Polynomial<int> p(k_ * n_);
  for (int i = 0; i < size_of_p_without_zeros; ++i) {
    p[i] = t_prime_polynomial[i] % (2 << c - 1);
  }
  // std::cout << "Recovered Polynomial p: " << p << std::endl;  ---- P is well calculated!!!

  std::string recovered_ct_str = "";
  for (int i = 0; i < (size_of_p_without_zeros - 1); ++i) {
    recovered_ct_str += std::bitset<2>(p[i]).to_string();
  }
  Bytes recovered_ct = Bytes::FromBitsToBytes(recovered_ct_str);

  std::cout << "Recovered Ciphertext: " << recovered_ct.FromBytesToHex() << std::endl;


  Bytes m_prime = cypher_box->Decrypt(recovered_ct);
  std::pair<Matrix<Polynomial<int>>, int> result_sk_n = sampling_unit_->GenerateDistribuitionMatrix(m_prime, n1_, 0);
  // std::cout <<  result_sk_n.first << std::endl;
}
