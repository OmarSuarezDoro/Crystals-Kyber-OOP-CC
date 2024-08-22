/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date August 22 2024
 * @version v0.1.0
 * @brief This file contains the definition of the MessageParser, which is used to parse the messages
 */

#include "MessageParser.h"

/**
 * @brief This method allows to fill a message so that it has a length multiple of sizeChunk
 * 
 * @param message : The message that is going to be filled.
 * @param sizeChunk : The length that the message should be multiple.
 * @return std::pair<std::string, int> : The resulting message and the padding length.
 */
std::pair<std::string, int> MessageParser::PadMessage(const std::string& message, int sizeChunk) {
  int temp = message.length() % sizeChunk;
  if (temp == 0) {
      return {message, 0};
  }
  int pad_len = sizeChunk - temp;
  std::string padding(pad_len, static_cast<char>(pad_len));
  return {message + padding, pad_len};
}

/**
 * @brief This method allows to remove the padding of a message
 * 
 * @param padded_message : The message that is going to be unpadded.
 * @return std::string : The resulting message without padding.
 */
std::string MessageParser::unpad(const std::string& padded_message) {
  unsigned char pad_len = padded_message.back();
  return padded_message.substr(0, padded_message.length() - pad_len);
}

/**
 * @brief This method allows to split a message in chunks of size sizeChunks
 * 
 * @param message : The message that is going to be split.
 * @param sizeChunks : The size of the chunks.
 * @return std::vector<std::string> : The resulting vector of strings.
 */
std::vector<std::string> MessageParser::SplitMessageInChunks(const std::string& message, int sizeChunks) {
  std::vector<std::string> blocks;
  for (size_t i = 0; i < message.length(); i += sizeChunks) {
      blocks.push_back(message.substr(i, sizeChunks));
  }
  return blocks;
}