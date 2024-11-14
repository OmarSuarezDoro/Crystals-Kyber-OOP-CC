/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date August 20 2024
 * @version v0.1.0
 * @brief This file contains the value and the initialization of the constants of the Kyber cryptosystem
 */

#pragma once


namespace KyberConstants {
  inline int N = 256;
  inline int Q = 3329;
  inline int K = 2;
  inline int N1 = 3;
  inline int N2 = 2;
  inline int Du = 10;
  inline int Dv = 4;
  inline int PkSize = 800;
  inline int SkSize = 1632;
  inline int CtSize = 768;
  inline int SeedSize = 32;
}
