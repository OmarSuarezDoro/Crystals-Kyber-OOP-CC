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
    if (args[i] == OPTION_ITERATIONS_SHORT || args[i] == OPTION_ITERATIONS_LONG) {
      iterations_ = std::stol(args[i + 1]);
    }
    if (args[i] == OPTION_CYPHER_BOX_SHORT || args[i] == OPTION_CYPHER_BOX_LONG) {
      if (args[i + 1] == "mceliece-348864") {
        cypher_box_option_ = MCELIECE_348864;
      }
      if (args[i + 1] == "mceliece-460896") {
        cypher_box_option_ = MCELIECE_460896;
      }
      if (args[i + 1] == "frodokem-1344-shake") {
        cypher_box_option_ = FRODOKEM_1344_SHAKE;
      }
      if (args[i + 1] == "frodokem-640-shake") {
        cypher_box_option_ = FRODOKEM_640_SHAKE;
      }
      if (args[i + 1] == "kyber-kem-512") {
        cypher_box_option_ = KYBER_KEM_512_OQS;
      }
    }
    ++i;
  }}

/**
 * @brief Run the program
 * @param option : The option to choose the parameters of the Kyber cryptosystem
 * @param seed : The seed to generate the rho and sigma values
 */
void ProgramInterface::run(int option, const std::vector<int>& seed) {
  // Initialize Kyber object
  std::unique_ptr<Kyber> kyber = std::make_unique<Kyber>(specification_, std::vector<int>(), cypher_box_option_);
  for (long i = 0; i < iterations_; ++i) {
    // Pad & Split the message
    std::pair<std::string, int> message_padlen = MessageParser::PadMessage(input_message_);
    std::vector<std::string> message_blocks = MessageParser::SplitMessageInChunks(message_padlen.first);  
    // Start the process
    std::pair<Bytes, Bytes> keypair;
    std::vector<Bytes> cyphertexts(message_blocks.size());
    std::vector<Bytes> decryptedtexts(message_blocks.size());
    std::fstream archivo("resultados.txt", std::ios::app);
    
    #ifdef TIME
    auto start = std::chrono::high_resolution_clock::now();
    unsigned long long ciclosInicio = __rdtsc();
    #endif


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
    if (pair_ct_shareds.second != shared_secret) {
      throw "The shared secret is not the same";
    }
    #endif

    // Decrypt the message
    std::string decrypted_message;
    for (const Bytes& decryptedtext : decryptedtexts) {
      decrypted_message += decryptedtext.FromBytesToAscii();
    }
    if (message_padlen.second > 0) {
      decrypted_message = MessageParser::unpad(decrypted_message);
    }
    
    #ifdef TIME
    std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - start;
    unsigned long long ciclosFin = __rdtsc();
    unsigned long long ciclosTranscurridos = ciclosFin - ciclosInicio;
    archivo << elapsed.count() << ", " << ciclosTranscurridos << "\n";
    #ifdef DEBUG
    std::cout << "Decrypted message: " << decrypted_message << std::endl;
    std::cout << "Elapsed time: " << elapsed.count() << "s" << std::endl;
    std::cout << "Elapsed cycles: " << ciclosTranscurridos << std::endl;
    #endif
    #endif
  }
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

/**
 * @brief Encrypt the blocks of the message using the KEM
 * @param message_chunks : The vector of message chunks
 * @param operand : The vector of operands
 * @param key : The key to use
 */
void ProgramInterface::KEMEncryptBlocks_(const std::vector<std::string>& message_chunks, std::vector<Bytes>& operand, const Bytes& key) {
  for (int i = 0; i < operand.size(); ++i) {
    operand[i] = Bytes(message_chunks[i]) ^ key; 
  }
}

/**
 * @brief Decrypt the blocks of the message using the KEM
 * @param encrypted_messages : The vector of encrypted messages
 * @param operand : The vector of operands
 * @param key : The key to use
 */
void ProgramInterface::KEMDecryptBlocks_(const std::vector<Bytes>& encrypted_messages, std::vector<Bytes>& operand, const Bytes& key) {
  for (int i = 0; i < operand.size(); ++i) {
    operand[i] = encrypted_messages[i] ^ key; 
  }
}

