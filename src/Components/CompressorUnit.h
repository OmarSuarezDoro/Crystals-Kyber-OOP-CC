/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date August 20 2024
 * @version v0.1.0
 * @brief This file contains the  the header declaration of the class CompressorUnit, that
 * will be used to compress and decompress the messages in the lattice-based cryptosystem.
 */

#pragma once

#include <cmath>

#include "../DataStructures/Matrix.h"
#include "../DataStructures/Polynomial.h"
#include "../../.conf/constants_values.h"


class CompressorUnit {
 public:
  CompressorUnit(int q) { q_ = q; }
  Matrix<Polynomial<int>> CompressMatrix(const Matrix<Polynomial<int>>& matrix, int bits_per_coefficient) const;
  Matrix<Polynomial<int>> DecompressMatrix(const Matrix<Polynomial<int>>& matrix, int bits_per_coefficient) const;
  Polynomial<int> Compress_(const Polynomial<int>& polynomial, int bits_per_coefficient) const;
  Polynomial<int> Decompress_(const Polynomial<int>& polynomial, int bits_per_coefficient) const;
 private:
  int q_;
  double _round_up(double x) const { return std::round(x + 0.000001); }
};