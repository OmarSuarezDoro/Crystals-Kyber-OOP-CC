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
  bytes_ = {};
}

/**
 * @brief Construct a new Bytes:: Bytes object
 * 
 * @param kBytes : The bytes to be stored
 */
Bytes::Bytes(const std::string& kBytes): bytes_(kBytes.begin(), kBytes.end()) {

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
  bytes_ = {static_cast<unsigned char>(kByte)};
}

/**
 * @brief Construct a new Bytes:: Bytes object
 * 
 * @param kBytes : The bytes to be stored
 */
Bytes::Bytes(const std::vector<int>& kBytes) {
  bytes_ = std::vector<unsigned char>(kBytes.size());
  for (size_t i = 0; i < kBytes.size(); ++i) {
    if (kBytes[i] < 0 || kBytes[i] > 255) {
      throw std::invalid_argument("Byte value out of range.");
    }
    bytes_[i] = static_cast<unsigned char>(kBytes[i]);
  }
}

/**
 * @brief Construct a new Bytes:: Bytes object
 * 
 * @param kBytes : The bytes to be stored
 */
Bytes::Bytes(const std::vector<unsigned char>& kBytes) {
  for (size_t i = 0; i < kBytes.size(); ++i) {
    if (kBytes[i] < 0 || kBytes[i] > 255) {
      throw std::invalid_argument("Byte value out of range.");
    }
  }
  bytes_ = kBytes;
}

/**
 * @brief Destroy the Bytes:: Bytes object
 * 
 */
Bytes::~Bytes() {
  bytes_ = {};
}

/**
 * @brief Overload the + operator to concatenate two Bytes objects
 * 
 * @param kBytes : The Bytes object to be concatenated
 * @return Bytes : The concatenated Bytes object
 */
Bytes Bytes::operator+(const Bytes& kBytes) const {
  std::vector<unsigned char> result = bytes_;
  for (const auto& element : kBytes.GetBytes()) {
    result.push_back(element);
  }
  return Bytes(result);
}

/**
 * @brief Overload the ^ operator to xor two Bytes objects
 * 
 * @param kBytes : The Bytes object to be xored
 * @return Bytes : The xored Bytes object
 */
Bytes Bytes::operator^(const Bytes& kBytes) const {
  std::vector<unsigned char> result = {};
  std::vector<unsigned char> copy_bytes = bytes_;
  std::vector<unsigned char> copy_kBytes = kBytes.GetBytes();
  if (int(bytes_.size()) < kBytes.GetBytesSize()) {
    while (int(int(copy_bytes.size())) < kBytes.GetBytesSize()) { copy_bytes.push_back(0); }
  } else {
    while (int(copy_kBytes.size()) < int(bytes_.size())) { copy_kBytes.push_back(0); }
  }
  
  for (int i = 0; i < bytes_.size(); i++) {
    result.push_back(bytes_[i] ^ kBytes.GetBytes()[i]);
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
  std::vector<unsigned char> copy_bytes = bytes_;
  std::vector<unsigned char> copy_kBytes = kBytes.GetBytes();
  if (int(bytes_.size()) < kBytes.GetBytesSize()) {
    while (int(int(copy_bytes.size())) < kBytes.GetBytesSize()) { copy_bytes.push_back(0); }
  } else {
    while (int(copy_kBytes.size()) < bytes_.size()) { copy_kBytes.push_back(0); }
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
  std::vector<unsigned char> result = {};
  std::vector<unsigned char> copy_bytes = bytes_;
  std::vector<unsigned char> copy_kBytes = kBytes.GetBytes();
  if (bytes_.size() < kBytes.GetBytesSize()) {
    while (int(copy_bytes.size()) < kBytes.GetBytesSize()) { copy_bytes.push_back(0); }
  } else {
    while (copy_kBytes.size() < bytes_.size()) { copy_kBytes.push_back(0); }
  }

  for (int i = 0; i < bytes_.size(); ++i) {
    result.push_back(bytes_[i] & kBytes.GetBytes()[i]);
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
  std::vector<unsigned char> result = {};
  for (int i = 0; i < bytes_.size(); ++i) {
    result.push_back(bytes_[i] << kShift);
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
  std::vector<unsigned char> result = {};
  for (int i = 0; i < bytes_.size(); ++i) {
    result.push_back(bytes_[i] >> kShift);
  }
  return Bytes(result);
}

/**
 * @brief Overload the ~ operator to negate the Bytes object
 * 
 * @return Bytes : The negated Bytes object
 */
Bytes Bytes::operator~() const {
  std::vector<unsigned char> result = {};
  for (int i = 0; i < bytes_.size(); ++i) {
    result.push_back(~bytes_[i]);
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
  for (const auto& element : kBytes.GetBytes()) {
    bytes_.push_back(element);
  }
  return *this;
}

/**
 * @brief Overload the ^= operator to xor two Bytes objects
 * 
 * @param kBytes : The Bytes object to be xored
 * @return Bytes : The xored Bytes object
 */
Bytes Bytes::operator^=(const Bytes& kBytes) {
  std::vector<unsigned char> result = {};
  std::vector<unsigned char> copy_bytes = bytes_;
  std::vector<unsigned char> copy_kBytes = kBytes.GetBytes();
  if (bytes_.size() < kBytes.GetBytesSize()) {
    while (int(copy_bytes.size()) < kBytes.GetBytesSize()) { copy_bytes.push_back(0); }
  } else {
    while (copy_kBytes.size() < bytes_.size()) { copy_kBytes.push_back(0); }
  }

  for (int i = 0; i < int(bytes_.size()); i++) {
    result.push_back(bytes_[i] ^ kBytes.GetBytes()[i]);
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
  std::vector<unsigned char> result = {};
  std::vector<unsigned char> copy_bytes = bytes_;
  std::vector<unsigned char> copy_kBytes = kBytes.GetBytes();
  if (int(bytes_.size()) < kBytes.GetBytesSize()) {
    while (int(copy_bytes.size()) < kBytes.GetBytesSize()) { copy_bytes.push_back(0); }
  } else {
    while (copy_kBytes.size() < bytes_.size()) { copy_kBytes.push_back(0); }
  }

  for (int i = 0; i < int(bytes_.size()); ++i) {
    result.push_back(bytes_[i] | kBytes.GetBytes()[i]);
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
  std::vector<unsigned char> result = {};
  std::vector<unsigned char> copy_bytes = bytes_;
  std::vector<unsigned char> copy_kBytes = kBytes.GetBytes();
  if (int(bytes_.size()) < kBytes.GetBytesSize()) {
    while (int(copy_bytes.size()) < kBytes.GetBytesSize()) { copy_bytes.push_back(0); }
  } else {
    while (int(copy_kBytes.size()) < int(bytes_.size())) { copy_kBytes.push_back(0); }
  }
  for (int i = 0; i < int(bytes_.size()); ++i) {
    result.push_back(bytes_[i] & kBytes.GetBytes()[i]);
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
  std::vector<unsigned char> result = {};
  for (int i = 0; i < int(bytes_.size()); ++i) {
    result.push_back(bytes_[i] << kShift);
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
  for (auto& element : bytes_) {
    element >>= kShift;
  }
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

unsigned char Bytes::operator[](const Bytes& kBytes) {
  return bytes_[kBytes.GetBytes()[0]];
}

/**
 * @brief Get the Bytes object in Big Endian format
 * 
 * @return std::string : The Bytes object in Big Endian format
 */
Bytes Bytes::toBigEndian() const {
  std::vector<unsigned char> result = {};
  for (int i = bytes_.size() - 1; i >= 0; --i) {
    result.push_back(bytes_[i]);
  }
  return Bytes(result);
}

/**
 * @brief Convert the Bytes object to a string of bits
 * 
 * @return std::string : The string of bits
 */
std::string Bytes::FromBytesToBits() const {
  std::string result = "";
  for (int i = 0; i < int(bytes_.size()); ++i) {
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
Bytes Bytes::FromBitsToBytes(const std::string& kBits) {
  std::vector<unsigned char> result = {};
  for (int i = 0; i < int(kBits.size()); i += 8) {
    result.push_back(std::bitset<8>(kBits.substr(i, 8)).to_ulong());
  }
  return result;
}

/**
 * @brief Convert the Bytes object to a string of hexadecimal numbers
 * 
 * @return std::string : The string of hexadecimal numbers
 */
std::string Bytes::FromBytesToHex() const {
  std::string result = "";
  const char hex_chars[] = "0123456789abcdef";
  for (unsigned char byte : bytes_) {
    result += hex_chars[(byte >> 4) & 0x0F];
    result += hex_chars[byte & 0x0F];
  }
  return result;
}


/**
 * @brief Convert the Bytes object to a string of numbers
 * 
 * @return long : The number
 */
long Bytes::FromBytesToNumbers() const {
  long result = 0;
  for (int i = 0; i < int(bytes_.size()); ++i) {
    // Iterate through the bytes
    for (int j = 0; j < bytes_[i]; ++j) {
      if (((bytes_[i] >> j) & 1) == 1) {
        result += pow(2, i  * 8 + j);
      }
    }
  }
  return result;
}

/**
 * @brief Reverse the bits of the Bytes object
 * 
 * @return std::string : The reversed Bytes object
 */
Bytes Bytes::BitReverse(int length) const {
  std::vector<unsigned char> result = {};
  for (int i = int(bytes_.size()) - 1; i >= 0; --i) {
    std::bitset<8> bits(bytes_[i]);
    std::string bits_string = bits.to_string();
    std::reverse(bits_string.begin(), bits_string.end());
    result.push_back(std::bitset<8>(bits_string).to_ulong());
  }
  return Bytes(result);
}


/**
 * @brief Get a vector of intergers that represents each byte value
 * 
 * @return std::vector<int> : The vector of integers
 */
std::vector<int> Bytes::GetBytesAsNumbersVector() const {
  std::vector<int> result;
  for (const auto& c : bytes_) {
    result.push_back(int(c));
  }
  return result;
}

/**
 * @brief Get the first n bytes of the Bytes object
 * 
 * @param start_index : The index to start the extraction
 * @param kN : The number of bytes to extract
 * @return Bytes : The extracted Bytes object
 */
Bytes Bytes::GetNBytes(const int& start_index, const int& kN) const {
  std::vector<unsigned char> result = {};
  for (int i = start_index; i < (start_index + kN); ++i) {
    result.push_back(bytes_[i]);
  }
  return Bytes(result);
}

/**
 * @brief Set the Bytes object
 * 
 * @param kBytes : The Bytes object to be set
 */
void Bytes::SetBytes(const std::string& kBytes) {
  bytes_ = {};
  for (const auto& element : kBytes) {
    bytes_.push_back(static_cast<int>(static_cast<unsigned char>(element)));
  }
}


/**
 * @brief Change the direction of the Bytes object
 * 
 * @return Bytes : The Bytes object with the direction changed
 */
Bytes Bytes::ChangeByteDirection() const {
  std::vector<unsigned char> result = {};
  for (size_t i = 0; i < bytes_.size(); ++i) {
    std::bitset<8> bits(bytes_[i]);
    std::string bits_string = bits.to_string();
    std::reverse(bits_string.begin(), bits_string.end());
    result.push_back(std::bitset<8>(bits_string).to_ulong());
  }
  return Bytes(result);
}
