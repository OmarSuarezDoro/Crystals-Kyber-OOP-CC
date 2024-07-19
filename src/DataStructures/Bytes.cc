/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date July 18 2024
 * @version v0.1.0
 * @brief This file contains the implementation of the methods of the class Bytes
 */

#include "Bytes.h"

/**
 * @brief Construct a new Bytes:: Bytes object
 * 
 */
Bytes::Bytes() {
  bytes_ = "" + 0;
}

/**
 * @brief Construct a new Bytes:: Bytes object
 * 
 * @param kBytes : The bytes to be stored
 */
Bytes::Bytes(const std::string& kBytes) {
  bytes_ = kBytes;
}

/**
 * @brief Construct a new Bytes:: Bytes object
 * 
 * @param kBytes : The bytes to be stored
 */
Bytes::Bytes(const Bytes& kBytes) {
  bytes_ = kBytes.GetBytes();
}

/**
 * @brief Construct a new Bytes:: Bytes object
 * 
 * @param kByte : The byte to be stored
 */
Bytes::Bytes(const uint8_t& kByte) {
  bytes_ = "" + kByte;
}

/**
 * @brief Destroy the Bytes:: Bytes object
 * 
 */
Bytes::~Bytes() {
  bytes_ = "";
}

/**
 * @brief Overload the + operator to concatenate two Bytes objects
 * 
 * @param kBytes : The Bytes object to be concatenated
 * @return Bytes : The concatenated Bytes object
 */
Bytes Bytes::operator+(const Bytes& kBytes) const {
  return Bytes(bytes_ + kBytes.GetBytes());
}

/**
 * @brief Overload the ^ operator to xor two Bytes objects
 * 
 * @param kBytes : The Bytes object to be xored
 * @return Bytes : The xored Bytes object
 */
Bytes Bytes::operator^(const Bytes& kBytes) const {
  std::string result = "";
  std::string copy_bytes = bytes_;
  std::string copy_kBytes = kBytes.GetBytes();
  if (bytes_.size() < kBytes.GetBytesSize()) {
    while (copy_bytes.length() < kBytes.GetBytesSize()) { copy_bytes += "0"; }
  } else {
    while (copy_kBytes.length() < bytes_.size()) { copy_kBytes += "0"; }
  }
  
  for (int i = 0; i < bytes_.size(); i++) {
    result += bytes_[i] ^ kBytes.GetBytes()[i];
  }
  return Bytes(result);
}

/**
 * @brief Overload the | operator to or two Bytes objects
 * 
 * @param kBytes : The Bytes object to be or'ed
 * @return Bytes : The or'ed Bytes object
 */
Bytes Bytes::operator|(const Bytes& kBytes) const {
  std::string result = "";
  std::string copy_bytes = bytes_;
  std::string copy_kBytes = kBytes.GetBytes();
  if (bytes_.size() < kBytes.GetBytesSize()) {
    while (copy_bytes.length() < kBytes.GetBytesSize()) { copy_bytes += "0"; }
  } else {
    while (copy_kBytes.length() < bytes_.size()) { copy_kBytes += "0"; }
  }

  for (int i = 0; i < bytes_.size(); ++i) {
    result += bytes_[i] | kBytes.GetBytes()[i];
  }
  return Bytes(result);
}

/**
 * @brief Overload the & operator to and two Bytes objects
 * 
 * @param kBytes : The Bytes object to be and'ed
 * @return Bytes : The and'ed Bytes object
 */
Bytes Bytes::operator&(const Bytes& kBytes) const {
  std::string result = "";
  std::string copy_bytes = bytes_;
  std::string copy_kBytes = kBytes.GetBytes();
  if (bytes_.size() < kBytes.GetBytesSize()) {
    while (copy_bytes.length() < kBytes.GetBytesSize()) { copy_bytes += "0"; }
  } else {
    while (copy_kBytes.length() < bytes_.size()) { copy_kBytes += "0"; }
  }

  for (int i = 0; i < bytes_.size(); ++i) {
    result += bytes_[i] & kBytes.GetBytes()[i];
  }
  return Bytes(result);
}

/**
 * @brief Overload the << operator to shift the Bytes object to the left
 * 
 * @param kShift : The number of bits to shift
 * @return Bytes : The shifted Bytes object
 */
Bytes Bytes::operator<<(const int& kShift) const {
  std::string result = "";
  for (int i = 0; i < bytes_.size(); ++i) {
    result += bytes_[i] << kShift;
  }
  return Bytes(result);
}

/**
 * @brief Overload the >> operator to shift the Bytes object to the right
 * 
 * @param kShift : The number of bits to shift
 * @return Bytes : The shifted Bytes object
 */
Bytes Bytes::operator>>(const int& kShift) const {
  std::string result = "";
  int remain_shift = kShift;
  for (int i = 0; i < bytes_.size(); ++i) {
    // If the number of bits to shift is greater than 8 we need to store them and then shift the next byte
    if (remain_shift >= 8) {
      result += bytes_[i] >> remain_shift;
      remain_shift -= 8;
    } else {
      result += bytes_[i] >> remain_shift;
      result += bytes_[i + 1] << (8 - remain_shift);
    }
  }
  return result;
}

/**
 * @brief Overload the ~ operator to negate the Bytes object
 * 
 * @return Bytes : The negated Bytes object
 */
Bytes Bytes::operator~() const {
  std::string result = "";
  for (int i = 0; i < bytes_.size(); ++i) {
    result += ~bytes_[i];
  }
  return Bytes(result);
}

/**
 * @brief Overload the += operator to add two Bytes objects
 * 
 * @param kBytes : The Bytes object to be added
 * @return Bytes : The added Bytes object
 */
Bytes Bytes::operator+=(const Bytes& kBytes) {
  bytes_ += kBytes.GetBytes();
  return *this;
}

/**
 * @brief Overload the ^= operator to xor two Bytes objects
 * 
 * @param kBytes : The Bytes object to be xored
 * @return Bytes : The xored Bytes object
 */
Bytes Bytes::operator^=(const Bytes& kBytes) {
  std::string result = "";
  std::string copy_bytes = bytes_;
  std::string copy_kBytes = kBytes.GetBytes();
  if (bytes_.size() < kBytes.GetBytesSize()) {
    while (copy_bytes.length() < kBytes.GetBytesSize()) { copy_bytes += "0"; }
  } else {
    while (copy_kBytes.length() < bytes_.size()) { copy_kBytes += "0"; }
  }

  for (int i = 0; i < bytes_.size(); i++) {
    result += bytes_[i] ^ kBytes.GetBytes()[i];
  }
  bytes_ = result;
  return *this;
}

/**
 * @brief Overload the |= operator to or two Bytes objects
 * 
 * @param kBytes : The Bytes object to be or'ed
 * @return Bytes : The or'ed Bytes object
 */
Bytes Bytes::operator|=(const Bytes& kBytes) {
  std::string result = "";
  std::string copy_bytes = bytes_;
  std::string copy_kBytes = kBytes.GetBytes();
  if (bytes_.size() < kBytes.GetBytesSize()) {
    while (copy_bytes.length() < kBytes.GetBytesSize()) { copy_bytes += "0"; }
  } else {
    while (copy_kBytes.length() < bytes_.size()) { copy_kBytes += "0"; }
  }

  for (int i = 0; i < bytes_.size(); ++i) {
    result += bytes_[i] | kBytes.GetBytes()[i];
  }
  bytes_ = result;
  return *this;
}

/**
 * @brief Overload the &= operator to and two Bytes objects
 * 
 * @param kBytes : The Bytes object to be and'ed
 * @return Bytes : The and'ed Bytes object
 */
Bytes Bytes::operator&=(const Bytes& kBytes) {
  std::string result = "";
  std::string copy_bytes = bytes_;
  std::string copy_kBytes = kBytes.GetBytes();
  if (bytes_.size() < kBytes.GetBytesSize()) {
    while (copy_bytes.length() < kBytes.GetBytesSize()) { copy_bytes += "0"; }
  } else {
    while (copy_kBytes.length() < bytes_.size()) { copy_kBytes += "0"; }
  }

  for (int i = 0; i < bytes_.size(); ++i) {
    result += bytes_[i] & kBytes.GetBytes()[i];
  }
  bytes_ = result;
  return *this;
}

/**
 * @brief Overload the <<= operator to shift the Bytes object to the left
 * 
 * @param kShift : The number of bits to shift
 * @return Bytes : The shifted Bytes object
 */
Bytes Bytes::operator<<=(const int& kShift) {
  std::string result = "";
  for (int i = 0; i < bytes_.size(); ++i) {
    result += bytes_[i] << kShift;
  }
  bytes_ = result;
  return *this;
}

/**
 * @brief Overload the >>= operator to shift the Bytes object to the right
 * 
 * @param kShift : The number of bits to shift
 * @return Bytes : The shifted Bytes object
 */
Bytes Bytes::operator>>=(const int& kShift) {
  std::string result = "";
  int remain_shift = kShift;
  for (int i = 0; i < bytes_.size(); ++i) {
    // If the number of bits to shift is greater than 8 we need to store them and then shift the next byte
    if (remain_shift >= 8) {
      result += bytes_[i] >> remain_shift;
      remain_shift -= 8;
    } else {
      result += bytes_[i] >> remain_shift;
      result += bytes_[i + 1] << (8 - remain_shift);
    }
  }
  bytes_ = result;
  return *this;
}

/**
 * @brief Overload the == operator to compare two Bytes objects
 * 
 * @param kBytes : The Bytes object to be compared
 * @return true : If the Bytes objects are equal
 * @return false : If the Bytes objects are different
 */
bool Bytes::operator==(const Bytes& kBytes) const {
  return bytes_ == kBytes.GetBytes();
}

/**
 * @brief Overload the != operator to compare two Bytes objects
 * 
 * @param kBytes : The Bytes object to be compared
 * @return true : If the Bytes objects are different
 * @return false : If the Bytes objects are equal
 */
bool Bytes::operator!=(const Bytes& kBytes) const {
  return bytes_ != kBytes.GetBytes();
}

char Bytes::operator[](const Bytes& kBytes) {
  return bytes_[kBytes.GetBytes()[0]];
}

/**
 * @brief Get the Bytes object in Big Endian format
 * 
 * @return std::string : The Bytes object in Big Endian format
 */
std::string Bytes::toBigEndian() const {
  std::string result = "";
  for (int i = bytes_.size() - 1; i >= 0; --i) {
    result += bytes_[i];
  }
  return result;
}

/**
 * @brief Get the Bytes object in Little Endian format
 * 
 * @return std::string : The Bytes object in Little Endian format
 */
std::string Bytes::toLittleEndian() const {
  return bytes_;
}

/**
 * @brief Convert the Bytes object to a string of bits
 * 
 * @return std::string : The string of bits
 */
std::string Bytes::FromBytesToBits() const {
  std::string result = "";
  for (int i = 0; i < bytes_.size(); ++i) {
    result += std::bitset<8>(bytes_[i]).to_string();
  }
  return result;
}

/**
 * @brief Convert a string of bits to a Bytes object
 * 
 * @param kBits : The string of bits
 * @return std::string : The Bytes object
 */
std::string Bytes::FromBitsToBytes(const std::string& kBits) {
  std::string result = "";
  for (int i = 0; i < kBits.size(); i += 8) {
    result += std::bitset<8>(kBits.substr(i, 8)).to_ulong();
  }
  return result;
}