/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date August 20 2024
 * @version v0.1.0
 * @brief This file contains the tests for the Kyber class
 */

#include <gtest/gtest.h>
#include "../src/Kyber/KyberKEM.h"


class KyberKEMTest : public ::testing::Test {
 public:

 protected:
  virtual void SetUp() {
  
  }
  virtual void TearDown() {
    // Clean up the test cases
  }
};


TEST_F(KyberKEMTest, TestOfKEM) {
  KyberKEM kyber = KyberKEM(512);
  std::pair<Bytes, Bytes> pair_keys = kyber.KeyGen();
  std::pair<Bytes, Bytes> pair_encapsulation = kyber.KEMEncapsulation(pair_keys.first);
  Bytes decapsulation = kyber.KEMDecapsulation(pair_keys.second, pair_encapsulation.first);
  EXPECT_EQ(decapsulation, pair_encapsulation.second);
}
