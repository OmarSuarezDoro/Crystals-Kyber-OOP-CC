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

#include "NTT.h"


  /**
   * This method finds the first primitive root of n. 
   * That means, the first number which every power of it is different from 1, with prime q.
   * 
   * @param n The number to find the primitive root.
   * @return The first primitive root of n.
   */
int NTT::_FirstPrimitiveRoot(int n) {
  // Checking conditions
  if (!_IsPrime(q_)) {
    throw std::invalid_argument("Q must be a prime number.");
  }
  if ((q_ - 1) % n != 0) {
    throw std::invalid_argument("n must divide q - 1.");
  }
  
  // We are going to check if base^n = 1 and base to another lower power is not 1.
  for (int base = 2; base < q_; base++) {
    bool is_primitive_root = true;
    // Check if base is a primitive root
    for (int i = 1; i < n; i++) {
      if (_PowerWithMod(base, i, q_) == 1) {
        is_primitive_root = false;
        break;
      }
    }
    if (is_primitive_root && _PowerWithMod(base, n_, q_) == 1) {
      return base;
    }
  }
  throw std::invalid_argument("Primitive root not found.");
}


/**
 * This method calculates the power of a number with a module.
 * 
 * @param base The base number.
 * @param exp The exponent.
 * @param mod The module.
 * @return The result of the power with module.
 */
int NTT::_PowerWithMod(int base, int exp, int mod) {
  int result = 1;
  for (int i = 0; i < exp; i++) {
    result = (result * base);
  }
  return result & mod;
}

/**
 * This method checks if a number is prime.
 * 
 * @param n The number to check.
 * @return True if the number is prime, false otherwise.
 */
bool NTT::_IsPrime(int n) {
  if (n <= 1) {
    return false;
  }
  if (n <= 3) {
    return true;
  }
  if (n % 2 == 0 || n % 3 == 0) {
    return false;
  }
  for (int i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) {
      return false;
    }
  }
  return true;
}

// Polynomial<int> NTT::_NTT(const Polynomial<int>& kPolynomial) {
//   int n = kPolynomial.GetSize() + 1;
//   int phi = _FirstPrimitiveRoot(2 * n);
//   int counter = 1;
//   int mid_index = n / 2;
//   Polynomial<int> result = kPolynomial;
//   while (counter < n) {
//     for (int i = 0; i < counter; i++) {
//       int j1 = 2 * i * mid_index;
//       int j2 = j1 + mid_index - 1;

//       int S = _PowerWithMod(phi, _BitRev(counter + i, n), q_);
//       for (int j = j1; j <= j2; j++) {
//         int temp_element = result[j];
//         int temp_mirror_element = result[j + mid_index];
//         result[j] = (temp_element + temp_mirror_element * S) % q_;
//         result[j + mid_index] = (temp_element - temp_mirror_element * S) % q_;
//       }
//     }
//     counter = 2 * counter;
//     mid_index = mid_index / 2;
//   }
//   return result;
// }
