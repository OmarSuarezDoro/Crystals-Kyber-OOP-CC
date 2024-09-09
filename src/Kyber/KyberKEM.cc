/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date September 9 2024
 * @version v0.1.0
 * @brief This file contains the header definitions of the method of the class KyberKEM which
 * contains the implementation of the Kyber cryptosystem with the Kyber Key Encapsulation Mechanism
 */

#include "./KyberKEM.h"

/**
 * @brief Generate a key pair for the KEM
 * 
 * @return std::pair<Bytes, Bytes> : The generated key pair
 */
std::pair<Bytes, Bytes> KyberKEM::KeyGen() {
  auto start = std::chrono::high_resolution_clock::now();
  Bytes seed = GenerateSeed_(KyberConstants::SeedSize);

  #ifdef DEBUG
    std::cout << "Seed Generated: " << seed.FromBytesToHex() << std::endl;
  #endif
  
  std::pair<Bytes, Bytes> key_pair = Kyber::KeyGen();
  Bytes pk = key_pair.first;
  Bytes sk = key_pair.second + pk + Keccak::H(pk, 32) + seed;
  
  #ifdef DEBUG
    std::cout << "Secret Key: " << sk.FromBytesToHex() << std::endl;
  #endif
  
  #ifdef TIME
    std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - start;
    time_results_["KEMKeyGen"].push_back(elapsed.count());
  #endif

  return std::pair<Bytes, Bytes>{pk, sk};
}


/**
 * @brief Encapsulate a key
 * 
 * @param pk : The public key
 * @return std::pair<Bytes, Bytes> : The encapsulated key
 */
std::pair<Bytes, Bytes> KyberKEM::KEMEncapsulation(const Bytes& pk) {
  auto start = std::chrono::high_resolution_clock::now();
  Bytes message = Keccak::H(GenerateSeed_(KyberConstants::SeedSize), KyberConstants::SeedSize);

  #ifdef DEBUG
    std::cout << "Message: " << message.FromBytesToHex() << std::endl;
  #endif

  std::pair<Bytes, Bytes> pair = Keccak::G(message + Keccak::H(pk, KyberConstants::SeedSize));

  #ifdef DEBUG
    std::cout << "K' and r': " << pair.first.FromBytesToHex() << " " << pair.second.FromBytesToHex() << std::endl;
  #endif
  Bytes K_prime = pair.first;
  Bytes r = pair.second;
  Bytes c = Encryption(pk, message, r);
  Bytes K = Keccak::KDF(K_prime + Keccak::H(c, KyberConstants::SeedSize), KyberConstants::SeedSize);

  #ifdef DEBUG
    std::cout << "Ciphertext: " << c.FromBytesToHex() << std::endl;
    std::cout << "K: " << K.FromBytesToHex() << std::endl << std::endl;
  #endif

  #ifdef TIME
    std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - start;
    time_results_["KEMEncapsulation"].push_back(elapsed.count());
  #endif

  return std::pair<Bytes, Bytes>{c, K};
}


/**
 * @brief Decapsulate a key
 * 
 * @param sk : The secret key
 * @param ciphertext : The ciphertext to decapsulate
 * @return Bytes : The decapsulated key
 */
Bytes KyberKEM::KEMDecapsulation(const Bytes& sk, const Bytes& ciphertext) {
  auto start = std::chrono::high_resolution_clock::now();
  if (sk.GetBytesSize() != (24 * k_ * int(n_ / 8) + 96)) {
    throw std::invalid_argument("The secret key is not the correct size");
  }
  if (ciphertext.GetBytesSize() != (du_ * k_ * int(n_ / 8) + dv_ * int(n_ / 8))) {
    throw std::invalid_argument("The cyphered text is not the correct size");
  }
  int entry_index = 12 * k_ * int(n_ / 8);
  int following_index = 24 * k_ * int(n_ / 8);
  Bytes pk = sk.GetNBytes(entry_index, KyberConstants::PkSize);
  Bytes h = sk.GetNBytes(following_index + 32, 32);
  Bytes z = sk.GetNBytes(following_index + 64, 32);

  #ifdef DEBUG
    std::cout << "Public Key: " << pk.FromBytesToHex() << std::endl;
    std::cout << "H: " << h.FromBytesToHex() << std::endl;
    std::cout << "Z: " << z.FromBytesToHex() << std::endl;
  #endif


  // Decrypting the message
  Bytes m_prime = Decryption(sk, ciphertext);
  // Generating the K' and r' values
  std::pair<Bytes, Bytes> pair = Keccak::G(m_prime + h);
  Bytes K_prime = pair.first;
  Bytes r_prime = pair.second;
  // Encrypting the message again
  Bytes c_prime = Encryption(pk, m_prime, r_prime);

  #ifdef DEBUG
    std::cout << "Message Decrypted: " << m_prime.FromBytesToHex() << std::endl;
    std::cout << "K' and r': " << K_prime.FromBytesToHex() << " " << r_prime.FromBytesToHex() << std::endl;
    std::cout << "Ciphertext: " << c_prime.FromBytesToHex() << std::endl;
  #endif
  Bytes result = Keccak::KDF((c_prime == ciphertext ? K_prime : z) + Keccak::H(c_prime, 32), 32);
  
  #ifdef TIME
    std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - start;
    time_results_["KEMDecapsulation"].push_back(elapsed.count());
  #endif
  
  return result;
}