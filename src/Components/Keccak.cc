#include "Keccak.h"

Keccak::Keccak() {
}


Bytes Keccak::XOF(const Bytes& bytes32, const Bytes& a, const Bytes& b, int length) {
  Bytes input_bytes = bytes32 + a + b;
  return shake128(input_bytes, length);
}

Bytes Keccak::shake128(const Bytes& input_data, int output_length) {
  CryptoPP::SHAKE128 shake;
//   CryptoPP::byte* input = new CryptoPP::byte[input_data.GetBytesSize()];
//   std::memcpy(input, input_data.GetBytes().data(), input_data.GetBytesSize());
//   CryptoPP::byte* output = new CryptoPP::byte[output_length];
//   shake.TruncatedFinal(output, output_length);
//   std::string result = std::string(reinterpret_cast<char*>(output), output_length);
//   return result;
}
