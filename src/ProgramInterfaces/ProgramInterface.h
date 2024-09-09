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

#include <iostream>
#include <chrono>
#include <thread>

#include "../Kyber/KyberKEM.h"
#include "../Components/MessageParser.h"


#define OPTION_SPECIFICATION_SHORT "-s"
#define OPTION_SPECIFICATION_LONG "--specification"

#define OPTION_MESSAGE_SHORT "-m"
#define OPTION_MESSAGE_LONG "--message"

#define OPTION_HELP_SHORT "-h"
#define OPTION_HELP_LONG "--help"

#define OPTION_KEM_SHORT "-k"
#define OPTION_KEM_LONG "--kem"


class ProgramInterface { 
 public:
  ProgramInterface(const std::vector<std::string>& args);
  // run must can specify each parameter
  void run(int option = 512, const std::vector<int>& seed = {}, int n = 256, int q = 3329, int k = 3,
  int n1 = 8, int n2 = 256, int du = 10, int dv = 10, bool benchmarking = false);
  #ifdef BENCHMARKING
  void benchmark();
  #endif

 private:
  int specification_;
  std::map<std::string, Kyber*> time_results_;
  std::string input_message_ = "Sample Text that it is going to be encrypted and decrypted!";
  bool use_kem_ = false;
  
  static void EncryptBlocks_(const Bytes& public_key, const std::vector<std::string>& message_chunks, std::vector<Bytes>& ciphertexts, Kyber* kyber);
  static void DecryptBlocks_(const std::vector<Bytes>& ciphertexts, const Bytes& secret_key, std::vector<Bytes>& decryptedtexts, Kyber* kyber);
  static void ProcessBlock(int id, const Bytes& block, const Bytes& key, const Bytes& coins, std::vector<Bytes>& ciphertexts, Kyber* kyber);
  static void ProcessDecryptionBlock(int id, const Bytes& block, const Bytes& key, std::vector<Bytes>& decryptedtexts, Kyber* kyber);

};