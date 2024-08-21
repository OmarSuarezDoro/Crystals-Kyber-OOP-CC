/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date July 18 2024
 * @version v0.1.0
 * @brief This file contains the header declaration of the class NTT, which give us 
 * The Number Theorical Transformation.
 */

#pragma once

#include <stdexcept>
#include <cmath>

#include "../DataStructures/Matrix.h"
#include "../DataStructures/Bytes.h"


class NTT {
 public:
  NTT(int n, int q) { n_ = n; q_ = q; }
  // Getters
  int GetN() { return n_; }
  int GetQ() { return q_; }
  Polynomial<int> NTT_Kyber(const Polynomial<int>& kPolynomial, bool is_ntt) const;
  Polynomial<int> _NTT(const Polynomial<int>& kPolynomial) const;
  Polynomial<int> _INTT(const Polynomial<int>& kPolynomial) const;
  Polynomial<int> ParsePolynomial_(const Bytes& kBytes) const;

  
  int _FirstPrimitiveRoot(int n) const;
  int _BitReverse(int n, int bits) const;
  int _PowerWithMod(int base, int exp, int mod) const;

  Matrix<Polynomial<int>> GenerateMatrix_(int k_size, Bytes rho, bool traspose = false) const;
  

 private:
  int  n_ = 256;
  int  q_ = 3389;
  bool _IsPrime(int n) const;
};
