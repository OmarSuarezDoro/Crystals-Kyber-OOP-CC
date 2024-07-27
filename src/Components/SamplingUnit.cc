/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date July 18 2024
 * @version v0.1.0
 * @brief This file contains the implementation of the class SamplingUnit, which generates the samples using CBC distribution
 */

#include "SamplingUnit.h"


/**
 * @brief This method implements the Centralized Binomial Distribution (CBD) function.
 * 
 * @param input_bytes : The input bytes stream.
 * @param eta : The eta value is the size of the noise that is going to be generated.
 * @return Polynomial<int> 
 */
Polynomial<int> SamplingUnit::_CBD(const Bytes& input_bytes, int eta) {

  if (64 >= input_bytes.GetBytesSize()) {
    throw std::invalid_argument("Input length is not correct.");
  }
  Polynomial<int> coefficients(n_);
  // REALLY IMPORTANT TO REVERT THE BYTES HERE!!!
  Bytes reverted_input_byte = input_bytes.ChangeByteDirection();
  std::string list_of_bits = reverted_input_byte.FromBytesToBits();
  for (int i = 0; i < n_; i++) {
    int a = 0;
    int b = 0;
    for (int j = 0; j < eta; j++) {
      a += list_of_bits[2 * i * eta + j] - '0';
      b += list_of_bits[2 * i * eta + eta + j] - '0';
    }
    coefficients[i] = a - b;
  }
  return coefficients;
}

