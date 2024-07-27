/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date July 18 2024
 * @version v0.1.0
 * @brief This file contains the tests for the SamplingUnit class
 
 */

#include <gtest/gtest.h>

#include "../src/Components/SamplingUnit.h"
#include "../src/DataStructures/Polynomial.h"

class SamplingUnitTest : public ::testing::Test {
 public:
  SamplingUnit sampling_unit = SamplingUnit(2, 256);
  Bytes input_bytes1;
 protected:
  virtual void SetUp() {
    input_bytes1 = Bytes(std::vector<int>{186, 195, 50, 98, 161, 235, 54, 2, 222, 244, 8,
    213, 20, 183, 135, 219, 55, 97, 182, 77, 42, 181, 109, 105, 145, 67, 28, 142, 51, 
    196, 111, 123, 3, 210, 18, 190, 14, 106, 76, 213, 230, 80, 172, 58, 101, 201, 120, 
    11, 134, 115, 116, 62, 157, 66, 87, 184, 22, 135, 136, 25, 96, 126, 112, 190, 92, 
    170, 216, 38, 223, 92, 237, 32, 128, 125, 24, 242, 74, 181, 243, 60, 11, 39, 105, 
    138, 77, 24, 147, 125, 11, 35, 47, 249, 86, 220, 244, 200, 48, 72, 199, 239, 203, 
    182, 4, 210, 28, 136, 136, 27, 183, 173, 231, 64, 127, 186, 203, 206, 230, 255, 
    152, 211, 144, 72, 243, 82, 210, 166, 240, 161, 219, 22, 192, 169, 4, 49, 77, 93, 
    252, 50, 254, 111, 16, 191, 202, 135, 116, 210, 250, 182, 89, 164, 248, 75, 234, 
    235, 51, 58, 144, 105, 21, 98, 3, 237, 192, 148, 159, 181, 10, 191, 184, 37, 231, 
    74, 71, 71, 9, 95, 94, 90, 1, 91, 252, 34, 123, 143, 171, 218, 188, 102, 11, 51, 68, 65});

  }
  
  virtual void TearDown() {
    // Clean up the test cases
  }
};


/**
 * @brief Test for the _CBD() method.
 */
TEST_F(SamplingUnitTest, CBDTEST1) {
  Polynomial<int> result_poly = sampling_unit._CBD(input_bytes1, 3);
  std::vector<int> result_vector = {-2, 1, -1, 0, 0, 2, -2, -2, 0, -1, -1, 1, -1, 1, -1, 0, 0, -1, -1, 0, 0, 1, 1, -2,
   0, 0, 0, 0, 0, 0, 1, -1, 0, 1, 1, 3, 1, 1, 2, -1, 1, 0, 1, 0, 0, 1, 0, 1, 1, -2, 2, 1, 1, 0, 1, 0, -1, -1, 1, -1, 0,
   1, 1, 1, 2, 1, 3, 0, -1, -1, -1, -1, 2, 0, 0, 2, 3, 0, -2, 2, -1, -2, 3, -1, -1, -1, 1, -1, -2, 0, -1, 1, -1, 0, 1,
   -1, 0, 0, 3, 2, -1, 0, 0, 0, 0, 0, 0, 1, 2, 0, 1, 0, 1, 0, -1, 0, -1, 0, -2, -1, 1, 0, 1, 1, -1, 1, 2, -1, -2, -1,
   -1, -1, 1, 1, -1, 0, 1, -1, 1, 3, -1, 0, -3, 2, 1, 0, -2, -2, 0, -1, 2, 0, 1, -1, -1, -2, 0, 1, -2, -1, -1, 0, -1,
   -2, 0, 0, 0, -1, -2, 3, -2, 0, 1, 0, -1, -1, 1, 1, 1, 1, 0, -1, 1, 0, -1, 0, 2, 1, 0, -1, -2, 0, -1, 0, 0, -1, 0, 
   1, 2, -1, -3, 1, 0, -2, 0, 2, 1, 1, -1, 1, 1, 2, 0, 1, -1, -1, 0, 1, -2, 2, 0, -1, -2, 1, -3, 1, -1, -2, 0, 0, -1, 
   0, 0, -2, 1, 2, -1, 2, -2, 1, -2, 1, -1, 0, 2, 0, -1, 0, -2, -1, 0, 1, 0, -1, 0, -1};
  Polynomial<int> expected_poly(256);
  expected_poly.SetCoefficients(result_vector); 
  EXPECT_EQ(result_poly, expected_poly);
}


