/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date August 14 2024
 * @version v0.1.0
 * @brief This file contains the definition of methods of the class EncDecUnit, that
 * will encode and decode the messages in the lattice-based cryptosystem.
 */

#include "EncDecUnit.h"

/**
 * @brief This method encodes a polynomial into a bytes sequence. This method is used in serialization process.
 * 
 * @param polynomial : The polynomial that is going to be encoded
 * @param bits_per_coefficient : The bits per coefficient that is going to be used for representation
 * @return Bytes 
 */
Bytes EncDecUnit::encode_(const Polynomial<int>& polynomial, int bits_per_coefficient) const {
  if (bits_per_coefficient < 1) {
    // iterate through the vector and see the number of bits needed to represent the biggest coefficient
    int max_coefficient = 0;
    for (int i = 0; i < polynomial.GetSize(); i++) {
      int current_coefficient = std::bitset<32>(polynomial[i]).to_string().length();
      max_coefficient = std::max(max_coefficient, current_coefficient);
    }
    bits_per_coefficient = max_coefficient;
  }
  
  std::string result_string = "";
  for (const auto& element : polynomial.GetCoefficients()) {
    std::string binary_string = std::bitset<32>(element).to_string();
    // removing ceros until the number of bits is the same as bits_per_coefficient
    binary_string = binary_string.substr(32 - bits_per_coefficient);
    // reverse the string order
    std::reverse(binary_string.begin(), binary_string.end());
    result_string += binary_string;
  }
  while (result_string.length() % 8 != 0) { result_string += "0"; }
  Bytes result = Bytes::FromBitsToBytes(result_string);
  return result;
}

Polynomial<int> EncDecUnit::decode_(Bytes input_bytes, int bits_per_coefficient = 0) const {

}
