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

#include "./Kyber/Kyber.h"
 
std::unique_ptr<Kyber> kyber = nullptr;

void ProcessBlock(int id, const Bytes& block, const Bytes& key, const Bytes& coins, std::vector<Bytes>& ciphertexts) {
  ciphertexts[id] = kyber->Encryption(key, block, coins);
}

void ProcessDecryptionBlock(int id, const Bytes& block, const Bytes& key, std::vector<Bytes>& decryptedtexts) {
  decryptedtexts[id] = kyber->Decryption(key, block);
}

void EncryptBlocks(const Bytes& public_key, const std::vector<std::string>& message_chunks, std::vector<Bytes>& ciphertexts) {
  // Generate a 32 byte coins (0 or 1)
  Bytes coins = Bytes();
  for (int i = 0; i < 32; ++i) {
    coins += Bytes(std::vector<int>{rand() % 2});
  }
  std::vector<std::thread> threads;
  for (int i = 0; i < message_chunks.size(); ++i) {
    threads.push_back(std::thread(ProcessBlock, i, Bytes(message_chunks[i]), public_key, coins, std::ref(ciphertexts)));
  }
  for (std::thread& thread : threads) {
    thread.join();
  }
}

  void DecryptBlocks(const std::vector<Bytes>& ciphertexts, const Bytes& secret_key, std::vector<Bytes>& decryptedtexts) {
    std::vector<std::thread> threads;
    for (int i = 0; i < ciphertexts.size(); ++i) {
      threads.push_back(std::thread(ProcessDecryptionBlock, i, ciphertexts[i], secret_key, std::ref(decryptedtexts)));
    }
    for (std::thread& thread : threads) {
      thread.join();
    }
  }



int main(int argc, char const *argv[]) {
  int option = 512;
  std::string input_message = "";
  if (argc == 1) {
    std::cout << "Introduce the message to be hashed: ";
    std::cin >> input_message;
  } else {
    option = std::stoi(argv[1]);
    input_message = argv[2];
  }
  // Instantiate the Kyber cryptosystem
  kyber = std::make_unique<Kyber>(option);


  auto start = std::chrono::high_resolution_clock::now();
  std::pair<std::string, int> message_padlength = MessageParser::PadMessage(input_message);
  std::vector<std::string> message_chunks = MessageParser::SplitMessageInChunks(message_padlength.first, 32);

  // std::cout << "Kyber cryptosystem with option " << option << std::endl;
  std::pair<Bytes, Bytes> key_pair = kyber->KeyGen();
  // std::cout << "Puclic key: " << key_pair.first.FromBytesToHex() << std::endl;
  // std::cout << "Secret key: " << key_pair.second.FromBytesToHex() << std::endl;
  std::vector<Bytes> ciphertexts(message_chunks.size());
  EncryptBlocks(key_pair.first, message_chunks, ciphertexts);
  std::vector<Bytes> decryptedtexts(message_chunks.size());
  DecryptBlocks(ciphertexts, key_pair.second, decryptedtexts);
  std::string decrypted_message;
  for (const Bytes& decryptedtext : decryptedtexts) {
    decrypted_message += decryptedtext.FromBytesToAscii();
  }
  if (message_padlength.second > 0) {
    decrypted_message = MessageParser::unpad(decrypted_message);
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - start;
  std::cout << "Tiempo de ejecución: " << duration.count() << " segundos" << std::endl;
  std::cout << "Decrypted message: " << decrypted_message << std::endl;
  return 0;
}