/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date August 14 2024
 * @version v0.1.0
 * @brief This file contains the header declaration of the class PWMUnit, that 
 * will perform the pointwise multiplication in NTT.
 */


#include "../DataStructures/Polynomial.h"
#include "NTT.h"


class PWMUnit {
 public:
  PWMUnit(int n, int q) : n_{n}, q_{q} {}
  Polynomial<int> pointwise_(const Polynomial<int>& p, const Polynomial<int>& g);

 private:
  int n_;
  int q_;
  NTT ntt_{n_, q_};
};