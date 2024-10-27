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
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>
#include <x86intrin.h> 

#include "../Kyber/Kyber.h"
#include "./MessageParser.h"
#include "../Attack/KleptoKyber.h"


#define OPTION_SPECIFICATION_SHORT "-s"
#define OPTION_SPECIFICATION_LONG "--specification"

#define OPTION_MESSAGE_SHORT "-m"
#define OPTION_MESSAGE_LONG "--message"

#define OPTION_HELP_SHORT "-h"
#define OPTION_HELP_LONG "--help"

#define OPTION_ITERATIONS_SHORT "-i"
#define OPTION_ITERATIONS_LONG "--iterations"

#define OPTION_FILE_SHORT "-f"
#define OPTION_FILE_LONG "--file"

#define OPTION_CYPHER_BOX_SHORT "-c"
#define OPTION_CYPHER_BOX_LONG "--cypher-box"



class ProgramInterface { 
 public:
  ProgramInterface(const std::vector<std::string>& args);
  void run(int option = 512, const std::vector<int>& seed = {});
  
 private:
  int specification_;
  long number_of_instances_ = 0;
  std::string input_file_ = "";
  std::string input_message_ = "";
  int cypher_box_option_ = KYBER_CBOX;
  long iterations_ = 1;

  static void KEMEncryptBlocks_(const std::vector<std::string>& message_chunks, std::vector<Bytes>& operand, const Bytes& key);
  static void KEMDecryptBlocks_(const std::vector<Bytes>& encrypted_messages, std::vector<Bytes>& operand, const Bytes& key);
  static void EncryptBlocks_(const Bytes& public_key, const std::vector<std::string>& message_chunks, std::vector<Bytes>& ciphertexts, Kyber* kyber);
  static void DecryptBlocks_(const std::vector<Bytes>& ciphertexts, const Bytes& secret_key, std::vector<Bytes>& decryptedtexts, Kyber* kyber);
  static void ProcessBlock(int id, const Bytes& block, const Bytes& key, const Bytes& coins, std::vector<Bytes>& ciphertexts, Kyber* kyber);
  static void ProcessDecryptionBlock(int id, const Bytes& block, const Bytes& key, std::vector<Bytes>& decryptedtexts, Kyber* kyber);
};