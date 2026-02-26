#include "./AES-256-GCM.h"
#include <stdexcept>

std::vector<uint8_t> AES256GCM::GenerateRandom(size_t n) {
  std::vector<uint8_t> out(n);
  if (RAND_bytes(out.data(), n) != 1) throw std::runtime_error("RAND_bytes failed");
  return out;
}

std::pair<Bytes, Bytes> AES256GCM::Encrypt(const Bytes& input) {
  secret_key_ = GenerateRandom(32);

  std::vector<uint8_t> key = secret_key_;
  std::vector<uint8_t> nonce = GenerateRandom(12);

  auto plaintext = input.GetBytes();
  std::vector<uint8_t> ciphertext(plaintext.size());
  std::vector<uint8_t> tag(16);

  EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
  if (!ctx) throw std::runtime_error("CTX alloc failed");

  int len = 0, ciphertext_len = 0;

  if (EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr) != 1) throw std::runtime_error("EncryptInit failed");
  if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, nonce.size(), nullptr) != 1) throw std::runtime_error("Set IV length failed");
  if (EVP_EncryptInit_ex(ctx, nullptr, nullptr, key.data(), nonce.data()) != 1) throw std::runtime_error("Set key/iv failed");
  if (EVP_EncryptUpdate(ctx, ciphertext.data(), &len, plaintext.data(), plaintext.size()) != 1) throw std::runtime_error("EncryptUpdate failed");

  ciphertext_len = len;

  if (EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len) != 1) throw std::runtime_error("EncryptFinal failed");

  ciphertext_len += len;

  if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, tag.data()) != 1) throw std::runtime_error("Get tag failed");

  EVP_CIPHER_CTX_free(ctx);

  ciphertext.resize(ciphertext_len);

  std::vector<uint8_t> packed;
  packed.insert(packed.end(), nonce.begin(), nonce.end());
  packed.insert(packed.end(), tag.begin(), tag.end());
  packed.insert(packed.end(), ciphertext.begin(), ciphertext.end());

  return { Bytes(packed), Bytes(secret_key_) };
}

Bytes AES256GCM::Decrypt(const Bytes& cyphertext, const Bytes& sk) {
  if (sk.GetBytesSize() != 0) {
    secret_key_ = sk.GetBytes();
  }

  auto data = cyphertext.GetBytes();
  if (data.size() < 12 + 16) {
    throw std::runtime_error("Ciphertext too short");
  }

  // packed = nonce(12) || tag(16) || ct(...)
  std::vector<uint8_t> nonce(data.begin(), data.begin() + 12);
  std::vector<uint8_t> tag(data.begin() + 12, data.begin() + 12 + 16);
  std::vector<uint8_t> ct(data.begin() + 12 + 16, data.end());

  if (secret_key_.size() != 32) {
    throw std::runtime_error("Invalid secret key size (expected 32 bytes)");
  }

  std::vector<uint8_t> pt(ct.size());

  EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
  if (!ctx) throw std::runtime_error("CTX alloc failed");

  int len = 0;
  int pt_len = 0;

  if (EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr) != 1) {
    EVP_CIPHER_CTX_free(ctx);
    throw std::runtime_error("DecryptInit failed");
  }

  if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, (int)nonce.size(), nullptr) != 1) {
    EVP_CIPHER_CTX_free(ctx);
    throw std::runtime_error("Set IV length failed");
  }

  if (EVP_DecryptInit_ex(ctx, nullptr, nullptr, secret_key_.data(), nonce.data()) != 1) {
    EVP_CIPHER_CTX_free(ctx);
    throw std::runtime_error("Set key/iv failed");
  }

  if (EVP_DecryptUpdate(ctx, pt.data(), &len, ct.data(), (int)ct.size()) != 1) {
    EVP_CIPHER_CTX_free(ctx);
    throw std::runtime_error("DecryptUpdate failed");
  }
  pt_len = len;

  if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, (int)tag.size(), tag.data()) != 1) {
    EVP_CIPHER_CTX_free(ctx);
    throw std::runtime_error("Set tag failed");
  }

  int ok = EVP_DecryptFinal_ex(ctx, pt.data() + pt_len, &len);
  EVP_CIPHER_CTX_free(ctx);

  if (ok != 1) {
    throw std::runtime_error("Auth failed (tag mismatch)");
  }

  pt_len += len;
  pt.resize(pt_len);

  return Bytes(pt);
}