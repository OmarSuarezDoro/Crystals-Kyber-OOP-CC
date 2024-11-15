/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date August 20 2024
 * @version v0.1.0
 * @brief This file contains the header declaration of methods of the KletoKyber methods 
 */

#pragma once
#include <cmath>

#include "../Kyber/Kyber.h"
#include "./cyphers/mceliece-348864.h"


class KleptoKyber : public Kyber {
 public:
  KleptoKyber(int option, Bytes attacker_pk, Bytes attacker_sk, const std::vector<int>& seed = {});
  Bytes RunBackdoor();
  Matrix<Polynomial<int>> recoverSecretKey(const Bytes& pk);
 private:
  Polynomial<int> PackBitsIntoPolynomial_(const Bytes& ct, const Matrix<Polynomial<int>>& t, int c);
  Polynomial<int> ComputeCompensation_(const Polynomial<int>& p, const Polynomial<int>& t_polynomial, int c);
  bool IsWorkingWell_(const Polynomial<int>& p, const Polynomial<int>& t_polynomial, const Polynomial<int>& h, int c);
  std::string byteToReversedBits(unsigned char byte, int numBits = 2);
  Bytes attacker_pk_;
  Bytes attacker_sk_;
  std::unique_ptr<Cypher> cypher_box = std::make_unique<McEliece_348864>();
};