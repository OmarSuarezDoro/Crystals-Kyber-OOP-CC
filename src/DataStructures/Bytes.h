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
#include <cmath>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

#pragma once

class Bytes {
 public:
  Bytes();
  Bytes(const std::string& kBytes);
  Bytes(const Bytes& kBytes);
  Bytes(const uint8_t& kByte);
  Bytes(const std::vector<int>& kBytes);
  Bytes(const std::vector<unsigned char>& kBytes);

  ~Bytes();

  // Getters
  std::vector<unsigned char> GetBytes() const { return bytes_; }
  int GetBytesSize() const { return bytes_.size(); }

  // Setters
  void SetBytes(const std::string& kBytes);

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
  unsigned char operator[](const Bytes& kBytes);
  bool operator==(const Bytes& kBytes) const;
  bool operator!=(const Bytes& kBytes) const;


  // Methods
  Bytes toBigEndian() const;
  std::string FromBytesToBits() const;
  std::string FromBytesToHex() const;
  long FromBytesToNumbers() const;
  Bytes BitReverse(int length) const;
  Bytes GetNBytes(const int& start_index, const int& kN) const;
  std::vector<int> GetBytesAsNumbersVector() const;
  Bytes ChangeByteDirection() const;

  static Bytes FromBitsToBytes(const std::string& kBits);
  
 private:
  std::vector<unsigned char> bytes_ = {};  

};