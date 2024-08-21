/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date August 20 2024
 * @version v0.1.0
 * @brief This file contains the definition of methods of the class CompressorUnit, that
 * will be used to compress and decompress the messages in the lattice-based cryptosystem.
 */

#include "CompressorUnit.h"

/**
 * @brief This method compresses a polynomial by multiplying each coefficient by a number
 * 
 * @param polynomial : Polynomial to compress
 * @param bits_per_coefficient : Number of bits per coefficient representation
 * @return Polynomial<int> 
 */
Polynomial<int> CompressorUnit::Compress_(const Polynomial<int>& polynomial, int bits_per_coefficient) const {
  double compressed_coefficient = pow(2, bits_per_coefficient);
  double number = compressed_coefficient / q_;
  Polynomial<int> compressed_polynomial = Polynomial<int>(polynomial.GetSize());
  for (int i = 0; i < polynomial.GetSize(); i++) {
    compressed_polynomial[i] = int(_round_up(polynomial[i] * number)) % int(compressed_coefficient);
  }
  return compressed_polynomial;
}

/**
 * @brief This method decompresses a polynomial by dividing each coefficient by a number
 * 
 * @param polynomial : Polynomial to decompress
 * @param bits_per_coefficient : Number of bits per coefficient representation
 * @return Polynomial<int> 
 */
Polynomial<int> CompressorUnit::Decompress_(const Polynomial<int>& polynomial, int bits_per_coefficient) const {
  double number = q_ /  pow(2, bits_per_coefficient);
  Polynomial<int> decompressed_polynomial = Polynomial<int>(polynomial.GetSize());
  for (int i = 0; i < polynomial.GetSize(); i++) {
    decompressed_polynomial[i] = int(_round_up(polynomial[i] * number));
  }
  return decompressed_polynomial;
}

/**
 * @brief This method compresses a matrix of polynomials by compressing each polynomial
 * 
 * @param matrix : Matrix of polynomials to compress
 * @param bits_per_coefficient : Number of bits per coefficient representation
 * @return Matrix<Polynomial<int>> 
 */
Matrix<Polynomial<int>> CompressorUnit::CompressMatrix(const Matrix<Polynomial<int>>& matrix, int bits_per_coefficient) const {
  Matrix<Polynomial<int>> compressed_matrix = Matrix<Polynomial<int>>(matrix.GetRowsSize(), matrix.GetColumnsSize());
  for (int i = 0; i < matrix.GetRowsSize(); i++) {
    for (int j = 0; j < matrix.GetColumnsSize(); j++) {
      compressed_matrix(i, j) = Compress_(matrix(i, j), bits_per_coefficient);
    }
  }
  return compressed_matrix;
}

/**
 * @brief This method decompresses a matrix of polynomials by decompressing each polynomial
 * 
 * @param matrix : Matrix of polynomials to decompress
 * @param bits_per_coefficient : Number of bits per coefficient representation
 * @return Matrix<Polynomial<int>> 
 */
Matrix<Polynomial<int>> CompressorUnit::DecompressMatrix(const Matrix<Polynomial<int>>& matrix, int bits_per_coefficient) const {
  Matrix<Polynomial<int>> decompressed_matrix = Matrix<Polynomial<int>>(matrix.GetRowsSize(), matrix.GetColumnsSize(), matrix.GetSizeElements());
  for (int i = 0; i < matrix.GetRowsSize(); i++) {
    for (int j = 0; j < matrix.GetColumnsSize(); j++) {
      decompressed_matrix(i, j) = Decompress_(matrix(i, j), bits_per_coefficient);
    }
  }
  return decompressed_matrix;
}

