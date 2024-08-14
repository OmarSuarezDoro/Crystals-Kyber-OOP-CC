/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date August 14 2024
 * @version v0.1.0
 * @brief This file contains the definitions of methods of the class PWMUnit.
 */

#include "PWMUnit.h"

/**
 * @brief This function performs the pointwise multiplication of two polynomials
 * 
 * @param p : polynomial p
 * @param g : polynomial g
 * @return Polynomial<int> 
 */
Polynomial<int> PWMUnit::pointwise_(const Polynomial<int>& p, const Polynomial<int>& g) {
  int phi = ntt_._FirstPrimitiveRoot(n_);
  // If the degree of any polynomial is less than 256 we apply NTT 
  // we fill with zeros since it does not change the polynomial.
  Polynomial<int> p_filled = p;
  Polynomial<int> g_filled = g;
  if (p.GetSize() < n_) {
    p_filled = p_filled.ReturnAppend(Polynomial<int>(n_ - p.GetSize()));
  } 
  if (g.GetSize() < n_) {
    g_filled = g_filled.ReturnAppend(Polynomial<int>(n_ - g.GetSize()));
  }
  Polynomial<int> p_odd(0);
  Polynomial<int> p_even(0);
  Polynomial<int> g_odd(0);
  Polynomial<int> g_even(0);
  for (int i = 0; i < n_; i++) {
    if (i % 2 == 0) {
      p_even.append(p_filled[i]);
      g_even.append(g_filled[i]);
    } else {
      p_odd.append(p_filled[i]);
      g_odd.append(g_filled[i]);
    }
  }
  Polynomial<int> p_wise_mult_even = Polynomial<int>(0);
  Polynomial<int> p_wise_mult_odd = Polynomial<int>(0);
  bool pepe = false;
  for (int i = 0; i < n_; ++i) {
    int left = 0;
    int right = 0;
    if (i % 2 == 0) {
      int mid = i / 2;
      int left = (p_even[mid] * g_even[mid]) % q_;
      int phi_power = ntt_._PowerWithMod(phi, 2 * ntt_._BitReverse(mid, n_ / 2) + 1, q_);
      int right = (p_odd[mid] * g_odd[mid]) % q_;
      right = (right * phi_power) % q_;
      p_wise_mult_even.append((left + right) % q_);
    } else {
      int mid = (i - 1) / 2;
      int left = (p_even[mid] * g_odd[mid]) % q_;
      int right = (p_odd[mid] * g_even[mid]) % q_;
      p_wise_mult_odd.append((left + right) % q_);
    }
  }
  Polynomial<int> result = Polynomial<int>(n_);
  for (int i = 0; i < n_; i++) {
    result[i] = (i % 2 == 0) ? p_wise_mult_even[i / 2] : p_wise_mult_odd[(i - 1) / 2];
  }
  return result;
}

/**
 * @brief This method multiplies two matrices using pointwise multiplication in NTT
 * 
 * @param A The first matrix
 * @param B The second matrix
 * @return Matrix<Polynomial<int>> 
 */
Matrix<Polynomial<int>> PWMUnit::multMatrixViaNTT(const Matrix<Polynomial<int>>& A, const Matrix<Polynomial<int>>& B) {
  int rowsA = A.GetRowsSize();
  int columnsA = A.GetColumnsSize();
  int columnsB = B.GetColumnsSize();
  Matrix<Polynomial<int>> result(rowsA, columnsB);
  for (int i = 0; i < rowsA; ++i) {
    for (int j = 0; j < columnsB; ++j) {
      Polynomial<int> sum_polynomial = Polynomial<int>(n_);
        for (int k = 0; k < columnsA; ++k) {
          sum_polynomial = sum_polynomial + pointwise_(A(i, k), B(k, j));
        }
      result(i, j) = sum_polynomial;
    }
  }
  return result;
}
