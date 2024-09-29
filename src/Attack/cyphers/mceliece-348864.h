/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date September 14 2024
 * @version v0.1.0
 * @brief This file contains the declaration of the methods of the mceliece--348864 cypher class
 */

#pragma once

#include <iostream>
#include <stdexcept>

#include "./cypher.h"

class McEliece_348864 : public Cypher {
 public:
  McEliece_348864();
  ~McEliece_348864() { OQS_KEM_free(kem); }
  std::pair<Bytes, Bytes> Encrypt(const Bytes& message) override;
  Bytes Decrypt(const Bytes& cyphertext) override;

 private:
  OQS_KEM* kem;
};