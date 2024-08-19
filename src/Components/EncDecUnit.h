/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date August 14 2024
 * @version v0.1.0
 * @brief This file contains the header declaration of the class EncDecUnit, that
 * will encode and decode the messages in the lattice-based cryptosystem.
 */

#include "../DataStructures/Bytes.h"
#include "../DataStructures/Polynomial.h"

class EncDecUnit {
 public:
  EncDecUnit(int n) : n_{n} {}
  Bytes encode_(const Polynomial<int>& polynomial, int bits_per_coefficient = 0) const;  
 private:
  int n_;
};



