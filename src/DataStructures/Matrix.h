/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date July 18 2024
 * @version v0.1.0
 * @brief This file contains the header declaration and implementation of the class Matrix
 */

#include <vector>
#include <iostream>
#include <assert.h>

#include "Polynomial.h"


#define MAX_REPRESENTATION_SIZE 3

#pragma once

template <typename T>
class Matrix {
 public:
  Matrix(const unsigned int& kRows, const unsigned int& kColumns, const unsigned int& kSizeElements = 0);
  
  // Getters
  unsigned int GetColumnsSize() const { return columns_; }
  unsigned int GetRowsSize() const { return rows_; }

  // Operator overload
  const T& operator()(unsigned int index_rows, unsigned int index_cols) const;
  T& operator()(unsigned int index_rows, unsigned int index_cols);
  Matrix<T> operator+(const Matrix<T>& kMatrix2) const;
  template <typename B> friend std::ostream& operator<<(std::ostream& os, const Matrix<B>& kMatrix);

 private:
  unsigned int rows_;
  unsigned int columns_;
  std::vector<T> vector_;
};

/**
 * @brief Construct a new Matrix< T>:: Matrix object
 * 
 * @tparam T : Template type parameter
 * @param kRows : The number of rows
 * @param kColumns : The number of columns
 * @param kSizeElements : The size of the elements, if we are working with polynomials
 */
template <typename T>
Matrix<T>::Matrix(const unsigned int& kRows, const unsigned int& kColumns, const unsigned int& kSizeElements) {
  rows_ = kRows;
  columns_ = kColumns;
  if (kSizeElements == 0) {
    vector_ = std::vector<T>(kRows * kColumns, 0);
    return;
  }
  vector_ = std::vector<T>(kRows * kColumns, T(kSizeElements));
  return;
}


/**
 * @brief Operator overload for the << operator
 * 
 * @tparam T : Template type parameter
 * @param os : The output stream
 * @param kMatrix : The Matrix to be printed
 * @return std::ostream& 
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& kMatrix) {
  for (unsigned int i = 0; i < kMatrix.rows_; i++) {
    os << "(";
    for (unsigned int j = 0; j < kMatrix.columns_; j++) {
      bool condition = MAX_REPRESENTATION_SIZE < kMatrix.vector_[i * kMatrix.columns_ + j].GetSize();
      if (condition) {
        os << "a" << i + j;
      } else {
        os << kMatrix.vector_[i * kMatrix.columns_ + j];
      }
      os << ((kMatrix.columns_ == j + 1) ? ")" : ", ");
    }
    os << std::endl;
  }
  return os;
}

/**
 * @brief This method returns the element at the given index - A const version
 * 
 * @tparam T : Template type parameter
 * @param index_rows : The row index of the element to be returned
 * @param index_cols : The column index of the element to be returned
 * @return const T& 
 */
template <typename T>
const T& Matrix<T>::operator()(unsigned int index_rows, unsigned int index_cols) const {
  assert(index_rows < GetRowsSize() && index_cols < GetColumnsSize());
  return vector_[index_rows * GetColumnsSize() + index_cols];
}

/**
 * @brief This method returns the element at the given index
 * 
 * @tparam T : Template type parameter
 * @param index_rows : The row index of the element to be returned
 * @param index_cols : The column index of the element to be returned
 * @return T& 
 */
template <typename T>
T& Matrix<T>::operator()(unsigned int index_rows, unsigned int index_cols) {
  assert(index_rows < GetRowsSize() && index_cols < GetColumnsSize());
  return vector_[index_rows * GetColumnsSize() + index_cols];
}

/**
 * @brief This method adds two matrices
 * 
 * @tparam T : Template type parameter
 * @param kMatrix2 : The matrix to be added
 * @return Matrix<T> 
 */
template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& kMatrix2) const {
  assert(GetColumnsSize() == kMatrix2.GetColumnsSize() && GetRowsSize() == kMatrix2.GetRowsSize());
  Matrix<T> result(GetRowsSize(), GetColumnsSize());
  for (unsigned int i = 0; i < GetRowsSize(); i++) {
    for (unsigned int j = 0; j < GetColumnsSize(); j++) {
      result(i, j) = vector_[i * GetColumnsSize() + j] + kMatrix2(i, j);
    }
  }
  return result;
}
