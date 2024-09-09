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
ProgramInterface::ProgramInterface(const std::vector<std::string>& args) {
  if (args.size() < 3) {
    throw std::invalid_argument("The number of arguments is not correct");
  }
  int i = 0;
  while (args.size() > i) {
    if (args[i] == OPTION_SPECIFICATION_SHORT || args[i] == OPTION_SPECIFICATION_LONG) {
      specification_ = std::stoi(args[i + 1]);
    }
    if (args[i] == OPTION_MESSAGE_SHORT || args[i] == OPTION_MESSAGE_LONG) {
      input_message_ = args[i + 1];
    }
    if (args[i] == OPTION_HELP_SHORT || args[i] == OPTION_HELP_LONG) {
      std::cout << "Usage: " << std::endl;
      std::cout << "  " << OPTION_SPECIFICATION_SHORT << ", " << OPTION_SPECIFICATION_LONG << " <specification> :" << " The specification of the Kyber cryptosystem" << std::endl;
      std::cout << "  " << OPTION_MESSAGE_SHORT << ", " << OPTION_MESSAGE_LONG << " <message> :" << " The message to encrypt and decrypt" << std::endl;
      std::cout << "  " << OPTION_HELP_SHORT << ", " << OPTION_HELP_LONG << " :" << " Show the help menu" << std::endl;
      exit(0);
    }
    ++i;
  }






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
}

/**
 * @brief Run the program
 */
void ProgramInterface::Run() {
  

}