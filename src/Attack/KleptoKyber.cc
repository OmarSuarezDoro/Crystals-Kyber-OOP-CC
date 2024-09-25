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
  std::pair<Bytes, Bytes> pair_ct_sharedm = cypher_box->Encrypt(attacker_pk_);
  
  // std::cout << "Cyphertext: " << std::endl;
  // pair_ct_sharedm.first.PrintBytes();

  Bytes seed_a = GenerateSeed_(KyberConstants::SeedSize);
  // seed_a.PrintBytes();
  // std::cout << "Shared secret: " << std::endl;
  // pair_ct_sharedm.second.PrintBytes();
  Bytes seed_b = pair_ct_sharedm.second;
  // std::cout << "Seed B: " << std::endl;
  // seed_b.PrintBytes();
  Matrix<Polynomial<int>> a = ntt_->GenerateMatrix_(k_, seed_a, true);
  int N = 0;
  std::pair<Matrix<Polynomial<int>>, int> pair_s_counter = sampling_unit_->GenerateDistribuitionMatrix(seed_b, n1_, N);
  Matrix<Polynomial<int>> s_ntt = applyNTTMatrix_(pair_s_counter.first, k_);
  std::pair<Matrix<Polynomial<int>>, int> pair_e_counter = sampling_unit_->GenerateDistribuitionMatrix(seed_b, n1_, pair_s_counter.second);
  Matrix<Polynomial<int>> e_ntt = applyNTTMatrix_(pair_e_counter.first, k_);
  // t = INTT(â ◦ NTT(s)) + e

  Matrix<Polynomial<int>> t = applyNTTMatrix_(ntt_->multMatrixViaNTT(a, s_ntt), k_, false) + e_ntt;
  // std::cout << "Matrix T: " << t << std::endl;
  // std::cout << "Matrix T size: " << t.GetRowsSize() << " x " << t.GetColumnsSize() << std::endl;
  
  // ctbd = (bt0 , bt1 , . . . , btb ); c = ⌈b/(k · n)⌉
  int b = pair_ct_sharedm.first.GetBytesSize() * BYTE_SIZE;
  int c = b / (k_ * n_) + 1;
  // std::cout << "b: " << b << std::endl;
  // std::cout << "c: " << c << std::endl;

  // Initialize the polynomial p with c length - NOT SURE ABOUT THIS!!  
  Polynomial<int> p(b / c);

  // Pack the bits of the ciphertext into the polynomial p
  for (int i = 0; i < p.GetSize(); ++i) {
    p[i] = 0;
    for (int j = i * c; j < (i + 1) * c; ++j) {
      // Extract the bit from the corresponding position of the ciphertext
      int bit_j = pair_ct_sharedm.first.GetBit(j);
      // Pack this bit into the coefficient p[i] using bit shifting.
      p[i] += bit_j * (1 << (j - i * c));
    }
  }
  // std::cout << "Polynomial p: " << p << std::endl;

  Polynomial<int> h(p.GetSize());  

  // Transform the matrix t into a polynomial to calculate the compensation polynomial
  Polynomial<int> t_polynomial = t(0, 0);
  for (int i = 1 ; i < k_; ++i) {
    t_polynomial = t_polynomial.ReturnAppend(t(i, 0));
  }
  // std::cout << "Polynomial t: " << t_polynomial << std::endl;
  // std::cout << "Polynomial t size: " << t_polynomial.GetSize() << std::endl;

  // Compute the compensation polynomial
  for (int i = 0; i < p.GetSize(); ++i) {
    h[i] = (p[i] - t_polynomial[i]) % 2;
  }
  while (h.GetSize() < t_polynomial.GetSize()) {
    h.append(0);
  }
  // std::cout << "Polynomial h: " << h << std::endl;


  Polynomial<int> t_prime = t_polynomial + h;
  // std::cout << "Polynomial t_prime: " << t_prime << std::endl;
  std::cout << "Polynomial t_prime size: " << t_prime.GetSize() << std::endl;


  Matrix<Polynomial<int>> t_prime_matrix(k_, 1);
  int current_row = 0;
  for (int i = 0; i < t_prime.GetSize(); i += n_) {
    t_prime_matrix(current_row, 0) = ntt_->NTT_Kyber(t_prime.GetSubPolynomial(i, i + n_), true);
    current_row++;
  }
  // std::cout << "Matrix t_prime: " << t_prime_matrix << std::endl;
  // std::cout << encdec_unit_->EncodeMatrixToBytes(t_prime_matrix, 12).FromBytesToHex() << std::endl;
  
  return seed_a + encdec_unit_->EncodeMatrixToBytes(t_prime_matrix, 12);
}