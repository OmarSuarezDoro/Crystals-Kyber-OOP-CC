/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date July 18 2024
 * @version v0.1.0
 * @brief This file contains the header declaration of the class Bytes
 */
#include <bitset>
#include <string>

#pragma once

class Bytes {
 public:
  Bytes();
  Bytes(const std::string& kBytes);
  Bytes(const Bytes& kBytes);
  Bytes(const uint8_t& kByte);
  ~Bytes();

  // Getters
  std::string GetBytes() const { return bytes_; }
  int GetBytesSize() const { return bytes_.size(); }

  // Setters
  void SetBytes(const std::string& kBytes) { bytes_ = kBytes; }

  // Operator overload
  Bytes operator+(const Bytes& kBytes) const;
  Bytes operator^(const Bytes& kBytes) const;
  Bytes operator|(const Bytes& kBytes) const;
  Bytes operator&(const Bytes& kBytes) const;
  Bytes operator<<(const int& kShift) const;
  Bytes operator>>(const int& kShift) const;
  Bytes operator~() const;
  Bytes operator+=(const Bytes& kBytes);
  Bytes operator^=(const Bytes& kBytes);
  Bytes operator|=(const Bytes& kBytes);
  Bytes operator&=(const Bytes& kBytes);
  Bytes operator<<=(const int& kShift);
  Bytes operator>>=(const int& kShift);
  char operator[](const Bytes& kBytes);
  bool operator==(const Bytes& kBytes) const;
  bool operator!=(const Bytes& kBytes) const;


  // Methods
  std::string toBigEndian() const;
  std::string toLittleEndian() const;
  std::string FromBytesToBits() const;

  static std::string FromBitsToBytes(const std::string& kBits);
  
 private:
  std::string bytes_;  
};