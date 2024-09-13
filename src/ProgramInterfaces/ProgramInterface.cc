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

std::mutex mtx;


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

    if (args[i] == OPTION_KEM_SHORT || args[i] == OPTION_KEM_LONG) {
      use_kem_ = true;
    }

    if (args[i] == OPTION_HELP_SHORT || args[i] == OPTION_HELP_LONG) {
      std::cout << "Usage: " << std::endl;
      std::cout << "  " << OPTION_SPECIFICATION_SHORT << ", " << OPTION_SPECIFICATION_LONG << " <specification> :" << " The specification of the Kyber cryptosystem" << std::endl;
      std::cout << "  " << OPTION_MESSAGE_SHORT << ", " << OPTION_MESSAGE_LONG << " <message> :" << " The message to encrypt and decrypt" << std::endl;
      std::cout << "  " << OPTION_HELP_SHORT << ", " << OPTION_HELP_LONG << " :" << " Show the help menu" << std::endl;
      exit(0);
    }
    ++i;
  }}

void ProgramInterface::run(int option, const std::vector<int>& seed) {
  #ifndef ATTACK
  auto start = std::chrono::high_resolution_clock::now();
  std::unique_ptr<Kyber> kyber = nullptr;
  kyber = std::make_unique<Kyber>(specification_);
  std::pair<std::string, int> message_padlen = MessageParser::PadMessage(input_message_);
  std::vector<std::string> message_blocks = MessageParser::SplitMessageInChunks(message_padlen.first);  
  std::pair<Bytes, Bytes> keypair = kyber->KeyGen();
  
  std::vector<Bytes> cyphertexts(message_blocks.size());
  EncryptBlocks_(keypair.first, message_blocks, cyphertexts, kyber.get());
  std::vector<Bytes> decryptedtexts(message_blocks.size());
  DecryptBlocks_(cyphertexts, keypair.second, decryptedtexts, kyber.get());
  std::string decrypted_message;
  for (const Bytes& decryptedtext : decryptedtexts) {
    decrypted_message += decryptedtext.FromBytesToAscii();
  }
  if (message_padlen.second > 0) {
    decrypted_message = MessageParser::unpad(decrypted_message);
  }

  std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - start;
  std::cout << "Elapsed time: " << elapsed.count() << "s" << std::endl;

  #ifndef BENCHMARKING
  std::cout << "Decrypted Message: " << decrypted_message << std::endl;
  #endif

  #else
  std::unique_ptr<KleptoKyber> klepto_kyber = std::make_unique<KleptoKyber>(specification_, attacker_pk, seed);
  klepto_kyber->RunBackdoor();  
  #endif

}


void ProgramInterface::EncryptBlocks_(const Bytes& public_key, const std::vector<std::string>& message_chunks, std::vector<Bytes>& ciphertexts, Kyber* kyber) {
  // Generate a 32 byte coins (0 or 1)
  Bytes coins = Bytes();
  for (int i = 0; i < 32; ++i) {
    coins += Bytes(std::vector<int>{rand() % 2});
  }
  std::vector<std::thread> threads;
  for (int i = 0; i < message_chunks.size(); ++i) {
    threads.push_back(std::thread(ProcessBlock, i, Bytes(message_chunks[i]), public_key, coins, std::ref(ciphertexts), kyber));
  }
  for (std::thread& thread : threads) {
    thread.join();
  }
}

void ProgramInterface::DecryptBlocks_(const std::vector<Bytes>& ciphertexts, const Bytes& secret_key, std::vector<Bytes>& decryptedtexts, Kyber* kyber) {
  std::vector<std::thread> threads;
  for (int i = 0; i < ciphertexts.size(); ++i) {
    threads.push_back(std::thread(ProcessDecryptionBlock, i, ciphertexts[i], secret_key, std::ref(decryptedtexts), kyber));
  }
  for (std::thread& thread : threads) {
    thread.join();
  }
}

void ProgramInterface::ProcessBlock(int id, const Bytes& block, const Bytes& key, const Bytes& coins, std::vector<Bytes>& ciphertexts, Kyber* kyber) {
  ciphertexts[id] = kyber->Encryption(key, block, coins);
}

void ProgramInterface::ProcessDecryptionBlock(int id, const Bytes& block, const Bytes& key, std::vector<Bytes>& decryptedtexts, Kyber* kyber) {
  decryptedtexts[id] = kyber->Decryption(key, block);
}

