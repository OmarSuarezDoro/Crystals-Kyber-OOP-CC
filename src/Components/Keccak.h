/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date July 18 2024
 * @version v0.1.0
 * @brief This file contains the header declaration of the class Keccak, which give us 
 * some cryptographic functionalities.
 */

#include <string>
#include <tuple>
// #include <cryptopp/hex.h>
// #include <cryptopp/sha3.h>
#include <cryptopp/shake.h>
// #include <cryptopp/filters.h>

#include "../DataStructures/Bytes.h"

#pragma once

class Keccak {
public:
  Keccak();
  ~Keccak();

  Bytes XOF(const Bytes& bytes32, const Bytes& a, const Bytes& b, int length);
  std::tuple<Bytes, Bytes> G(const Bytes& input_bytes);
  Bytes H(const Bytes& input_bytes);
  static Bytes PRF(const Bytes& sigma, int byte_to_hash, int length);
  Bytes KDF(const Bytes& input_bytes, int length);

  // Métodos estáticos para operaciones SHAKE y SHA3
  static Bytes shake128(const Bytes& input_data, int output_length);
  static Bytes shake256(const Bytes& input_data, int output_length);
  static Bytes sha3_512(const Bytes& input_data);

 private:

};