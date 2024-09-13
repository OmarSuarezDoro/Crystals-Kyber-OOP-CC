/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date August 20 2024
 * @version v0.1.0
 * @brief This file contains the definition of the methods of the KletoKyber class 
 */

#include "./KleptoKyber.h"

KleptoKyber::KleptoKyber(int option, Bytes attacker_pk, const std::vector<int>& seed) : Kyber(option, seed) {
  attacker_pk_ = attacker_pk;
  pk_bd_mceliece_ = uint8_t{KyberConstants::PkSize};
  sk_bd_mceliece_ = uint8_t{KyberConstants::SkSize};
}

void KleptoKyber::RunBackdoor() {
  Bytes seed_b = GenerateSeed_(KyberConstants::SeedSize);

}


std::pair<Bytes, Bytes> KleptoKyber::BackdoorEncryption() {
  uint8_t ss_bd[1]; 
  uint8_t pk_aux[attacker_pk_.GetBytesSize()];
  // Copy the attacker public key to the auxiliary public key
  for (int i = 0; i < attacker_pk_.GetBytesSize(); i++) {
    pk_aux[i] = attacker_pk_[i];
  }

  uint8_t ct_aux[1];
  if (PQCLEAN_MCELIECE348864_CLEAN_crypto_kem_enc(ct_aux, ss_bd, pk_aux) != 0) {
    printf("Error en la encriptación del backdoor.\n");
    exit(1);
  }

  Bytes cyphered_text = Bytes(std::vector<int>{0});
  cyphered_text[0] = ct_aux[0];
  Bytes shared_secret = Bytes(std::vector<int>{0});
  shared_secret[0] = ss_bd[0];

  return std::make_pair(cyphered_text, shared_secret);
}