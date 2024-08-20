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

namespace KyberConstants {
  int N = 256;
  int Q = 3329;
  int K = 2;
  int N1 = 3;
  int N2 = 2;
  int Du = 10;
  int Dv = 4;
  int PkSize = 800;
  int SkSize = 1632;
  int CtSize = 768;
  int SeedSize = 32;

  void InitializeConstants(int option) {
    switch (option) {
      case 512:
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