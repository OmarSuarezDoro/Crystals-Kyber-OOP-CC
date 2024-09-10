/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date August 22 2024
 * @version v0.1.0
 * @brief This is the client program that uses the Kyber cryptosystem
 */

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>

#include "./ProgramInterfaces/ProgramInterface.h"

int main(int argc, char const *argv[]) {
  std::vector<std::string> args;
  for (int i = 0; i < argc; ++i) {
    args.push_back(argv[i]);
  }
  ProgramInterface program_interface(args);
  program_interface.run();
  return 0;
}