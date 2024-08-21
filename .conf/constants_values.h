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

#ifndef KYBERCONSTANTS_VALUES_H
#define KYBERCONSTANTS_VALUES_H

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

  void InitializeConstants(int option) {
    switch (option) {
      case 512:
        N = 256;
        Q = 3329;
        K = 2;
        N1 = 3;
        N2 = 2;
        Du = 10;
        Dv = 4;
        PkSize = 800;
        SkSize = 1632;
        CtSize = 768;
        SeedSize = 32;
        break;
      case 768:
        N = 256;
        Q = 3329;
        K = 3;
        N1 = 3;
        N2 = 2;
        Du = 10;
        Dv = 4;
        PkSize = 1184;
        SkSize = 2400;
        CtSize = 1088;
        break;
      case 1024:
        N = 256;
        Q = 3329;
        K = 4;
        N1 = 2;
        N2 = 2;
        Du = 11;
        Dv = 5;
        PkSize = 1568;
        SkSize = 3168;
        CtSize = 1568;
        break;
      default:
        break;
    }
  }
}

#endif