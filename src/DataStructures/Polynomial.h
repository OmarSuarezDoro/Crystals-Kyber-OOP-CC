/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date July 18 2024
 * @version v0.1.0
 * @brief This file contains the header declaration and implementation of the class Polynomial
 */

#include <vector>
#include <iostream>
#include <assert.h>

#pragma once

template <typename T>
class Polynomial {
 public:
  Polynomial(const unsigned int& kSize, const int& module = 3389);
  void append(const T& kElement) { vector_.push_back(kElement); }
  Polynomial<T> ReturnAppend(const Polynomial<T>& kElements); 

  // Getters
  int GetSize() const { return vector_.size(); }
  std::vector<T> GetCoefficients() const { return vector_; }
  // Setters
  void SetCoefficients(const std::vector<T>& kCoefficients) { vector_ = kCoefficients; }
  // Operator overload
  const T& operator[](int index) const;
  T& operator[](int index);
  Polynomial<T> operator+(const Polynomial<T>& kPolynomial2) const;
  Polynomial<T> operator-(const Polynomial<T>& kPolynomial2) const;
  bool operator==(const Polynomial<T>& kPolynomial2) const;
  bool operator!=(const Polynomial<T>& kPolynomial2) const { return !(*this == kPolynomial2); }
  
  template <typename B> friend std::ostream& operator<<(std::ostream& os, const Polynomial<B> kPolynomial);
 private:
  std::vector<T> vector_;
  int module_;
};

/**
 * @brief Construct a new Polynomial< T>:: Polynomial object
 * 
 * @tparam T : Template type parameter
 * @param kSize : The size of the polynomial
 */
template <typename T>
Polynomial<T>::Polynomial(const unsigned int& kSize, const int& module) {
  module_ = module;
  vector_ = std::vector<T>(int(kSize), 0);
}


/**
 * @brief Operator overload for the << operator
 * 
 * @tparam T : Template type parameter
 * @param os : The output stream
 * @param kPolynomial : The polynomial to be printed
 * @return std::ostream& 
 */
template <typename T>
std::ostream& operator<<(std::ostream& os, const Polynomial<T> kPolynomial) {
  const int kSize = kPolynomial.vector_.size() - 1;
  int i = 0;
  os << "[";
  for (const auto& element : kPolynomial.vector_) {
    os << element << (kSize == i++ ? "]" : ", ");
  }
  return os;
}

/**
 * @brief This method returns the element at the given index - A const version
 * 
 * @tparam T : Template type parameter
 * @param index : The index of the element to be returned
 * @return const T& 
 */
template <typename T> 
const T& Polynomial<T>::operator[](int index) const {
  assert(index < GetSize());
  return vector_[index];
}

/**
 * @brief This method returns the element at the given index
 * 
 * @tparam T : Template type parameter
 * @param index : The index of the element to be returned
 * @return T& 
 */
template <typename T> 
T& Polynomial<T>::operator[](int index) {
  assert(index < GetSize());
  return vector_[index];
}

/**
 * @brief This method adds two polynomials
 * 
 * @tparam T : Template type parameter
 * @param kPolynomial2 : The polynomial to be added
 * @return Polynomial<T> 
 */
template <typename T>
Polynomial<T> Polynomial<T>::operator+(const Polynomial<T>& kPolynomial2) const {
  assert(GetSize() == kPolynomial2.GetSize());
  Polynomial<T> result(GetSize());
  for (int i = 0; i < GetSize(); i++) {
    result[i] = (vector_[i] + kPolynomial2[i]) % module_;
  }
  return result;
}

/**
 * @brief This method subtracts two polynomials
 * 
 * @tparam T : Template type parameter
 * @param kPolynomial2 : The polynomial to be subtracted
 * @return Polynomial<T> 
 */
template <typename T>
Polynomial<T> Polynomial<T>::operator-(const Polynomial<T>& kPolynomial2) const {
  assert(GetSize() == kPolynomial2.GetSize());
  Polynomial<T> result(GetSize());
  for (int i = 0; i < GetSize(); i++) {
    result[i] = vector_[i] - kPolynomial2[i];
  }
  return result;
}

/**
 * @brief This method checks if two polynomials are equal
 * 
 * @tparam T : Template type parameter
 * @param kPolynomial2 : The polynomial to be compared
 * @return bool
 */
template <typename T>
bool Polynomial<T>::operator==(const Polynomial<T>& kPolynomial2) const {
  assert(GetSize() == kPolynomial2.GetSize());
  for (int i = 0; i < GetSize(); i++) {
    if (vector_[i] != kPolynomial2[i]) {
      return false;
    }
  }
  return true;
}



/**
 * @brief This method appends a polynomial to another
 * 
 * @tparam T : Template type parameter
 * @param kElements : The polynomial to be appended
 * @return Polynomial<T> 
 */
template <typename T>
Polynomial<T> Polynomial<T>::ReturnAppend(const Polynomial<T>& kElements) {
  Polynomial<T> result(GetSize() + kElements.GetSize());
  int limit = GetSize() + kElements.GetSize();
  for (int i = 0 ; i < GetSize(); i++) {
    result[i] = vector_[i];
  }
  for (int i = GetSize(); i < limit; i++) {
    result[i] = kElements[i - GetSize()];
  }
  return result;
}