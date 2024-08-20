/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date August 20 2024
 * @version v0.1.0
 * @brief This file contains the definitions of the methods of the class Kyber
 */

#include "Kyber.h"


Kyber::Kyber(int option) {
  KyberConstants::InitializeConstants(option);
  n_ = KyberConstants::N;
  q_ = KyberConstants::Q;
  k_ = KyberConstants::K;
  n1_ = KyberConstants::N1;
  n2_ = KyberConstants::N2;
  du_ = KyberConstants::Du;
  dv_ = KyberConstants::Dv;  
}


