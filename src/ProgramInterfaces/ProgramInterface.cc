/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date September 5 2024
 * @version v0.1.0
 * @brief This file contains the definition of ProgramInterface methods
 */

#include "./ProgramInterface.h"

/**
 * @brief Construct a new Program Interface:: Program Interface object
 * @param args : The arguments passed to the program 
 */
ProgramInterface::ProgramInterface(char* const args[]) {
  specification_ = std::stoi(args[1]);
  kyber_ = std::make_unique<Kyber>(specification_); // Specification that it is going to be used
  #ifdef DEBUG
    std::cout << "Kyber cryptosystem with option " << specification_ << std::endl;
  #endif
  #ifdef TIME
    time_results_ = {
      {"KeyGen", {}},
      {"Encryption", {}},
      {"Decryption", {}},
      {"Padding", {}},
      {"Unpadding", {}},
      {"Splitting", {}}
    };
  #endif
  if (args[2] != nullptr) {
    input_message_ = args[2];
  }
}

/**
 * @brief Run the program
 */
void ProgramInterface::Run() {
  

}