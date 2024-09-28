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
    if (args[i] == OPTION_FILE_SHORT || args[i] == OPTION_FILE_LONG) {
      std::ifstream file(args[i + 1]);
      input_file_ = args[i + 1];
      if (!file.is_open()) {
        throw std::invalid_argument("The file could not be opened");
      }
      std::stringstream buffer;
      buffer << file.rdbuf();
      file.close();
      input_message_ = buffer.str();
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

/**
 * @brief Run the program
 * @param option : The option to choose the parameters of the Kyber cryptosystem
 * @param seed : The seed to generate the rho and sigma values
 */
void ProgramInterface::run(int option, const std::vector<int>& seed) {
  #ifdef TIME
  auto start = std::chrono::high_resolution_clock::now();
  #endif
  // Initialize Kyber object
  std::unique_ptr<Kyber> kyber = std::make_unique<Kyber>(specification_);
  // Pad & Split the message
  std::pair<std::string, int> message_padlen = MessageParser::PadMessage(input_message_);
  std::vector<std::string> message_blocks = MessageParser::SplitMessageInChunks(message_padlen.first);  
  // Start the process
  std::pair<Bytes, Bytes> keypair;
  std::vector<Bytes> cyphertexts(message_blocks.size());
  std::vector<Bytes> decryptedtexts(message_blocks.size());

  #ifndef KEM
  keypair = kyber->KeyGen();
  EncryptBlocks_(keypair.first, message_blocks, cyphertexts, kyber.get());
  DecryptBlocks_(cyphertexts, keypair.second, decryptedtexts, kyber.get());
  #else
  keypair = kyber->KEMKeyGen();
  // Encapsulate the shared secret
  std::pair<Bytes, Bytes> pair_ct_shareds = kyber->KEMEncapsulation(keypair.first);
  KEMEncryptBlocks_(message_blocks, cyphertexts, pair_ct_shareds.second);
  // Decapsulate the shared secret
  Bytes shared_secret = kyber->KEMDecapsulation(keypair.second, pair_ct_shareds.first);
  decryptedtexts = cyphertexts;
  KEMDecryptBlocks_(cyphertexts, decryptedtexts, shared_secret);
  #endif

  // 2. Encrypt the message
  std::string decrypted_message;
  for (const Bytes& decryptedtext : decryptedtexts) {
    decrypted_message += decryptedtext.FromBytesToAscii();
  }
  if (message_padlen.second > 0) {
    decrypted_message = MessageParser::unpad(decrypted_message);
  }
  
  #ifdef TIME
  std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - start;
  std::cout << "Decrypted message: " << decrypted_message << std::endl;
  std::cout << "Elapsed time: " << elapsed.count() << "s" << std::endl;
  #endif
}

/**
 * @brief Encrypt the blocks of the message
 * @param public_key : The public key
 * @param message_chunks : The vector of message chunks
 * @param ciphertexts : The vector of ciphertexts
 * @param kyber : The Kyber object
 */
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

/**
 * @brief Decrypt the blocks of the message
 * @param ciphertexts : The vector of ciphertexts
 * @param secret_key : The secret key
 * @param decryptedtexts : The vector of decrypted texts
 * @param kyber : The Kyber object
 */
void ProgramInterface::DecryptBlocks_(const std::vector<Bytes>& ciphertexts, const Bytes& secret_key, std::vector<Bytes>& decryptedtexts, Kyber* kyber) {
  std::vector<std::thread> threads;
  for (int i = 0; i < ciphertexts.size(); ++i) {
    threads.push_back(std::thread(ProcessDecryptionBlock, i, ciphertexts[i], secret_key, std::ref(decryptedtexts), kyber));
  }
  for (std::thread& thread : threads) {
    thread.join();
  }
}

/**
 * @brief Process a block of the message
 * @param id : The id of the block
 * @param block : The block to process
 * @param key : The key to use
 * @param coins : The coins to use
 * @param ciphertexts : The vector of ciphertexts
 * @param kyber : The Kyber object
 */
void ProgramInterface::ProcessBlock(int id, const Bytes& block, const Bytes& key, const Bytes& coins, std::vector<Bytes>& ciphertexts, Kyber* kyber) {
  ciphertexts[id] = kyber->Encryption(key, block, coins);
}

/**
 * @brief Process the decryption of a block
 * @param id : The id of the block
 * @param block : The block to decrypt
 * @param key : The key to use
 * @param decryptedtexts : The vector of decrypted texts
 * @param kyber : The Kyber object
 */
void ProgramInterface::ProcessDecryptionBlock(int id, const Bytes& block, const Bytes& key, std::vector<Bytes>& decryptedtexts, Kyber* kyber) {
  decryptedtexts[id] = kyber->Decryption(key, block);
}


