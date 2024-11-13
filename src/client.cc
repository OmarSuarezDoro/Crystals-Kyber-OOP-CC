/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date August 22 2024
 * @version v0.1.0
 * @brief This is the client program that uses the Kyber cryptosystem
 */

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>

#include "./Attack/KleptoKyber.h"
#include "./ProgramInterfaces/ProgramInterface.h"

int main(int argc, char const *argv[]) {
  #ifndef ATTACK
  std::vector<std::string> args;
  for (int i = 0; i < argc; ++i) {
    args.push_back(argv[i]);
  }
  ProgramInterface program_interface(args);
  for (int i = 0; i < 10000; ++i) {
    program_interface.run();
  }  
  #else
  Kyber kyber(512, {}, MCELIECE_348864);
  std::pair<Bytes, Bytes> pair = kyber.KEMKeyGen();
  Bytes attacker_pk = pair.first;
  Bytes attacker_sk = pair.second;
  // std::cout << "Public Key: " << attacker_pk.FromBytesToHex() << std::endl
  //           << "Secret Key: " << attacker_sk.FromBytesToHex() << std::endl;
  KleptoKyber klepto_kyber(512, attacker_pk, attacker_sk, {});
  Bytes result = klepto_kyber.RunBackdoor();
  klepto_kyber.recoverSecretKey(result);
  #endif
  return 0;
}