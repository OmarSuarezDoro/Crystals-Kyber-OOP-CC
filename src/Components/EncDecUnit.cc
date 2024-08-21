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
 * @brief This method encodes a matrix of polynomials into a bytes sequence. This method is used in serialization process.
 * 
 * @param input_matrix : The matrix that is going to be encoded
 * @param bits_per_coefficient : The bits per coefficient that is going to be used for representation
 * @return Bytes 
 */
Bytes EncDecUnit::EncodeMatrixToBytes(const Matrix<Polynomial<int>>& input_matrix, const int bits_per_coefficient) const {
  Bytes result = Bytes();
  for (int i = 0; i < input_matrix.GetRowsSize(); i++) {
    for (int j = 0; j < input_matrix.GetColumnsSize(); j++) {
      Bytes current_bytes = encode_(input_matrix(i, j), bits_per_coefficient);
      result += current_bytes;
    }
  }
  return result;
}



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



/**
 * @brief This method encodes a matrix of polynomials into a bytes sequence. This method is used in serialization process.
 * 
 * @param input_bytes The bytes sequence that is going to be decoded
 * @param rows The number of rows of the matrix
 * @param cols The number of columns of the matrix
 * @param length The length of the bytes sequence
 * @return Matrix<Polynomial<int>> 
 */
Matrix<Polynomial<int>> EncDecUnit::DecodeBytesToMatrix(const Bytes& input_bytes, const int rows, const int cols, int length) const {
  if (length < 1) {
    int denominator = n_ * rows * cols;
    length = (8 * input_bytes.GetBytesSize()) / denominator;
    int reminder = (8 * input_bytes.GetBytesSize()) % denominator;
    if (reminder != 0) {
      throw std::invalid_argument("The input byte list must have a length multiple of 32.");
    }
    if (n_ * length * rows * cols > 8 * input_bytes.GetBytesSize()) {
      throw std::invalid_argument("The length of the bytes must be smaller for the length that was indicated.");
    }
  }
  int chunk_length = 32 * length;
  std::vector<Bytes> coefficients = {};
  int i = 0;
  for (i; (i + chunk_length) < input_bytes.GetBytesSize(); i += chunk_length) {
    Bytes chunk = input_bytes.GetNBytes(i, chunk_length);
    coefficients.push_back(chunk); 
  }
  // Take the last chunk, if it is needed
  if (i < input_bytes.GetBytesSize()) {
    Bytes chunk = input_bytes.GetNBytes(i, input_bytes.GetBytesSize() - i);
    coefficients.push_back(chunk);
  }
  Matrix<Polynomial<int>> result = Matrix<Polynomial<int>>(rows, cols, n_);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      Bytes current_bytes = coefficients[i * cols + j];
      Polynomial<int> current_polynomial = decode_(current_bytes, length);
      result(i, j) = current_polynomial;
    }
  }
  return result;
}


/**
 * @brief This method decodes a bytes sequence into a polynomial. This method is used in deserialization process.
 * 
 * @param input_bytes : The bytes sequence that is going to be decoded
 * @param bits_per_coefficient : The bits per coefficient that is going to be used for representation
 * @return Polynomial<int> 
 */
Polynomial<int> EncDecUnit::decode_(const Bytes& input_bytes, int bits_per_coefficient) const {
  if (bits_per_coefficient < 1) {
    bits_per_coefficient = (8 * input_bytes.GetBytesSize()) / n_;
    int reminder = (8 * input_bytes.GetBytesSize()) % n_;
    if (reminder != 0) {
      throw std::invalid_argument("The input byte list must have a length multiple of 32.");
    }
  }
  if ((n_ * bits_per_coefficient) != (8 * input_bytes.GetBytesSize())) {
    throw std::invalid_argument("The input byte list must have a length multiple of 32.");
  }
  Polynomial<int> coefficients = Polynomial<int>(n_);
  Bytes copy_bytes = input_bytes.toBigEndian();
  std::string binary_string = copy_bytes.FromBytesToBits();

  for (int i = 0; i < n_; i++) {
    coefficients[i] = 0;
    for (int j = 0; j < bits_per_coefficient; j++) {
      coefficients[i] += (binary_string[i * bits_per_coefficient + j] - '0') << j;
    }
  }
  return coefficients;
}

