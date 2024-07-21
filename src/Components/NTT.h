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

#include <stdexcept>
#include <cmath>

#include "../DataStructures/Matrix.h"

#pragma once

class NTT {
 public:
  NTT(int n, int q) { n_ = n; q_ = q; }
  // Getters
  int GetN() { return n_; }
  int GetQ() { return q_; }
  

 private:
  int  n_ = 256;
  int  q_ = 3389;
  bool _IsPrime(int n);
  int _FirstPrimitiveRoot(int n);
  int _PowerWithMod(int base, int exp, int mod);
  Polynomial<int> _NTT(const Polynomial<int>& kPolynomial);
  Polynomial<int> _InverseNTT(const Polynomial<int>& kPolynomial);
};
