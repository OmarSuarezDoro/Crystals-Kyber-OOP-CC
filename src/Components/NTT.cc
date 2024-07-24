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
 * @brief This method applies the Number Theorical Transformation to a polynomial.
 * 
 * @param kPolynomial : The polynomial to apply the NTT.
 * @return Polynomial<int> 
 */
Polynomial<int> NTT::_NTT(const Polynomial<int>& kPolynomial) {
  int n = kPolynomial.GetSize();
  int phi = _FirstPrimitiveRoot(2 * n);
  int mid_index = n / 2;
  // std::cout << "Mid index: " << mid_index << std::endl;
  Polynomial<int> result = kPolynomial;
  // Iterating over the polynomial - First we chunk the polynomial in sizes of 2 * i
  for (int i = 1; i < n; i *= 2) {
    // Iterating over the chunk that we've created
    for (int j = 0; j < i; ++j) {
      int left_interval = 2 * j * mid_index; 
      int right_interval = left_interval + mid_index - 1;
      int S = _PowerWithMod(phi, _BitReverse(i + j, n), q_);
      // std::cout << "i " << i << " j " << j << " => j1: " << left_interval << " j2: " << right_interval << std::endl;
      // Iterating over the chunk - TODO: Fix this segmentation fault
      for (int k = left_interval; k <= right_interval; ++k) {
        int temp_element = result[k];
        int temp_mirror_element = result[k + mid_index];
        result[k] = (temp_element + temp_mirror_element * S) % q_;
        result[k + mid_index] = (temp_element - temp_mirror_element * S) % q_;
        while (result[k] < 0) { result[k] += q_; }
        while (result[k + mid_index] < 0) { result[k + mid_index] += q_; }
        // std::cout << "k: " << k << " k + mid_index: " << k + mid_index << " S: " << S << " temp_element: " << temp_element << " temp_mirror_element: " << temp_mirror_element << std::endl;
      }
    }
    mid_index /= 2;
  }
  // for (int i = 0; i < n; ++i) {
  //   std::cout << result[i] << " ";
  // }
  // std::cout << std::endl;
  exit(0);
  return result;
}

/**
 * @brief This method applies the Inverse Number Theorical Transformation to a polynomial.
 * 
 * @param kPolynomial : The polynomial to apply the INTT.
 * @return Polynomial<int> 
 */
Polynomial<int> NTT::_INTT(const Polynomial<int>& kPolynomial) {
  int n = kPolynomial.GetSize();
  int phi = _FirstPrimitiveRoot(2 * n);
  int phi_inverse = _PowerWithMod(phi, 2 * n - 1, q_);
  Polynomial<int> result = kPolynomial;
  int mid_index = n / 2;
  int k = 1;
  while (mid_index > 0) {
    for (int i = 0; i < mid_index; ++i) {
      int left_interval = 2 * i * k;
      int right_interval = left_interval + k - 1;
      int S = _PowerWithMod(phi_inverse, _BitReverse(mid_index + i, n), q_);
      for (int j = left_interval; j <= right_interval; ++j) {
        int temp_element = result[j];
        int temp_mirror_element = result[j + k];
        result[j] = (temp_element + temp_mirror_element) % q_;
        result[j + k] = ((temp_element - temp_mirror_element) * S) % q_;
        while (result[j] < 0) { result[j] += q_; }
        while (result[j + k] < 0) { result[j + k] += q_; }

      }      
    }
    mid_index /= 2;
    k *= 2;
  }
  // Every element in Zq pow q - 2 = inverse of n.
  int n_inverse = _PowerWithMod(n, q_ - 2 , q_);
  for (int i = 0; i < n; ++i) {
    result[i] = (result[i] * n_inverse) % q_; 
  }
  std::cout << result << std::endl;
  exit(0);
  return result;
}


int NTT::_BitReverse(int element, int length_of_sequence) {
  // Generar la secuencia inicial
  std::vector<int> seq(length_of_sequence);
  for (int i = 0; i < length_of_sequence; ++i) {
    seq[i] = i;
  }
  
  int m = std::log2(length_of_sequence);
  std::vector<int> out(length_of_sequence, 0);

  for (int i = 0; i < length_of_sequence; ++i) {
    std::bitset<32> bin(i);
    std::string bin_str = bin.to_string().substr(32 - m);
    std::reverse(bin_str.begin(), bin_str.end());
    int j = std::stoi(bin_str, nullptr, 2);
    out[j] = seq[i];
  }
  return out[element];
}

  /**
   * This method finds the first primitive root of n. 
   * That means, the first number which every power of it is different from 1, with prime q.
   * 
   * @param n The number to find the primitive root.
   * @return The first primitive root of n.
   */
int NTT::_FirstPrimitiveRoot(int n) { // 256
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
    for (int i = 1; i < n; ++i) {
      if (_PowerWithMod(base, i, q_) == 1) {
        is_primitive_root = false;
        break;
      }
    }
    if (is_primitive_root && _PowerWithMod(base, n, q_) == 1) {
      return base;
    }
    if (base ==17) { exit(0); }
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
  base = base % mod;
  while (exp > 0) {
    if (exp % 2 == 1) {
      result = (result * base) % mod;
    }
    exp = exp >> 1;
    base = (base * base) % mod;
    while (base < 0) {
      base += mod;
    }
  }
  return result;
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