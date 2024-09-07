/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date September 5 2024
 * @version v0.1.0
 * @brief This file contains the header declaration of class ProgramInterface
 */

#pragma once

#include <chrono>
#include "../Kyber/Kyber.h"


class ProgramInterface { 
 public:
  ProgramInterface(char* const args[]);
  virtual void Run();

 private:
  int specification_;
  std::unique_ptr<Kyber> kyber_;
  std::map<std::string, std::vector<double>> time_results_;
  std::string input_message_ = "Sample Text that it is going to be encrypted and decrypted!";
};