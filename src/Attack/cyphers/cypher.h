/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date September 14 2024
 * @version v0.1.0
 * @brief This file contains the declaration of the methods of the Cypher class  
 */

#include <oqs/oqs.h>

#include "../../DataStructures/Bytes.h"

class Cypher {
 public:
  Cypher() = default;
  virtual std::pair<Bytes, Bytes> Encrypt(const Bytes& pk) = 0;
  virtual Bytes Decrypt(const Bytes& cyphertext) = 0;
 private:
};