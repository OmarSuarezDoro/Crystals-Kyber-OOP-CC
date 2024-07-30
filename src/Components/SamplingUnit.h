/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date July 18 2024
 * @version v0.1.0
 * @brief This file contains the header declaration of the class SamplingUnit, which generates the samples using CBC distribution
 */

#include "../Components/Keccak.h"
#include "../DataStructures/Bytes.h"
#include "../DataStructures/Polynomial.h"
#include "../DataStructures/Matrix.h"

class SamplingUnit {
 public:
  SamplingUnit(int k, int n) { k_ = k; n_ = n; };
  Polynomial<int> _CBD(const Bytes& input_bytes, int eta);
  Matrix<Polynomial<int>> GenerateDistribuitionMatrix(const Bytes& input_bytes, int eta, int N);

 private:
  int k_;
  int n_;

};