#pragma once
#include "cypher.h"
#include <openssl/evp.h>
#include <openssl/rand.h>

class AES256GCM : public Cypher {
 public:
  AES256GCM() = default;

  std::pair<Bytes, Bytes> Encrypt(const Bytes& input) override;
  Bytes Decrypt(const Bytes& cyphertext, const Bytes& sk = Bytes()) override;

 private:
  std::vector<uint8_t> GenerateRandom(size_t n);
};