/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date September 9 2024
 * @version v0.1.0
 * @brief This file contains the header declaration of the class KyberKEM which
 * contains the implementation of the Kyber cryptosystem with the Kyber Key Encapsulation Mechanism
 */

#pragma once

#include "./Kyber.h"

class KyberKEM : public Kyber {
 public:
  KyberKEM(int option, const std::vector<int>& seed = {}, int n = 256, int q = 3329, int k = 2,
  int n1 = 3, int n2 = 2, int du = 10, int dv = 4, bool benchmarking = false) : Kyber(option, seed, n, q, k, n1, n2, du, dv, benchmarking) {}
  virtual std::pair<Bytes, Bytes> KeyGen();
  std::pair<Bytes, Bytes> KEMEncapsulation(const Bytes& pk);
  Bytes KEMDecapsulation(const Bytes& sk, const Bytes& ciphertext);
 private:
};