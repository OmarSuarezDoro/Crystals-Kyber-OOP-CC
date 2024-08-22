#include <iostream>
#include <string>

#include "./Kyber/Kyber.h"

// Bits interpretados de derecha izquierda (como normalmente sería)
// Mientras que los bytes se interpretan de izquierda a derecha
int main(int argc, char const *argv[]) {
  int option = 512;
  std::string input_message = "";
  if (argc == 1) {
    std::cout << "Introduce the message to be hashed: ";
    std::cin >> input_message;
  } else {
    option = std::stoi(argv[1]);
    input_message = argv[2];
  }
  std::pair<std::string, int> message_padlength = MessageParser::PadMessage(input_message);
  std::vector<std::string> message_chunks = MessageParser::SplitMessageInChunks(message_padlength.first, 32);
  std::cout << "Kyber cryptosystem with option " << option << std::endl;
  Kyber kyber(option);
  std::pair<Bytes, Bytes> key_pair = kyber.KeyGen();
  std::cout << "Puclic key: " << key_pair.first.FromBytesToHex() << std::endl;
  std::cout << "Secret key: " << key_pair.second.FromBytesToHex() << std::endl;
  std::vector<Bytes> ciphertexts;
  // Encrypt the message
  for (const std::string& chunk : message_chunks) {
    std::cout << "Chunk: " << chunk << std::endl;
    Bytes message = Bytes(chunk);
    Bytes ciphertext = kyber.Encryption(key_pair.first, message, key_pair.first);
    std::cout << "Ciphertext: " << ciphertext.FromBytesToHex() << std::endl;
    ciphertexts.push_back(ciphertext);
  }
  std::cout << "Ciphertexts generated" << std::endl;
  Bytes decrypted_message_concatenated;
  // Decrypt the message
  for (const Bytes& ciphertext : ciphertexts) {
    Bytes decrypted_message = kyber.Decryption(key_pair.second, ciphertext);
    std::cout << "Decrypted message: " << decrypted_message.FromBytesToHex() << std::endl;
    decrypted_message_concatenated += decrypted_message;
  }
  // Concatenate the decrypted messages
  std::string decrypted_message = decrypted_message_concatenated.FromBytesToAscii();
  if (message_padlength.second > 0) {
    decrypted_message = MessageParser::unpad(decrypted_message);
  }
  std::cout << "Decrypted message: " << decrypted_message << std::endl;
  return 0;
}