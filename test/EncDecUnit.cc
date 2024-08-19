/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date August 14 2024
 * @version v0.1.0
 * @brief This file contains the tests for the EncDecUnit class
 */

#include <gtest/gtest.h>
#include "../src/Components/EncDecUnit.h"
#include "../src/DataStructures/Bytes.h"

class EncDecUnitTest : public ::testing::Test {
 public:
  Polynomial<int> test_polynomial1 = Polynomial<int>(256);
  Polynomial<int> test_polynomial2 = Polynomial<int>(256);

 protected:
  virtual void SetUp() {
    // Set up the test cases
    test_polynomial1.SetCoefficients({2625, 2266, 3256, 2071, 1525, 18, 262, 2227, 3053, 2349, 1584, 3328, 2711, 2902, 2032,
     1896, 179, 1105, 384, 3211, 217, 2904, 1454, 1538, 962, 641, 49, 2494, 2847, 514, 3313, 1902, 1636, 751, 2398, 1715, 
     2864, 1303, 1630, 2890, 1226, 1087, 1221, 1236, 2047, 912, 2140, 1041, 495, 441, 2328, 3243, 2530, 3174, 1371, 96, 
     2701, 178, 3179, 1429, 263, 1621, 802, 777, 1687, 740, 724, 702, 687, 1692, 3106, 169, 790, 1613, 666, 1012, 3195, 
     614, 2402, 1972, 656, 2781, 1354, 982, 430, 2193, 1917, 682, 542, 407, 877, 2656, 1259, 3123, 1140, 1001, 2192, 3066, 
     3209, 3268, 2003, 970, 1215, 2613, 258, 2854, 723, 675, 1921, 2610, 769, 1235, 2577, 961, 731, 136, 12, 910, 1767, 737, 
     648, 530, 3126, 2790, 2899, 283, 1008, 535, 525, 2170, 3111, 811, 1458, 514, 776, 831, 28, 2274, 772, 2511, 871, 2420, 
     2862, 3218, 1771, 1420, 2932, 15, 2752, 289, 3026, 2472, 1632, 2539, 1605, 950, 504, 3117, 2497, 2758, 1152, 611, 2837, 
     813, 1836, 2066, 2902, 2707, 88, 167, 2390, 733, 2602, 3129, 1342, 2909, 1090, 1929, 1011, 1929, 2976, 1053, 2106, 1846, 
     1934, 2731, 234, 2771, 1376, 170, 523, 3008, 2323, 2672, 1258, 412, 156, 2222, 686, 1562, 487, 591, 98, 2886, 1685, 2005, 
     981, 1085, 2, 2500, 2531, 610, 1384, 2478, 2561, 1912, 3147, 1893, 363, 3285, 2561, 2361, 1484, 2596, 635, 158, 2918, 1771, 
     3024, 2650, 2517, 2065, 533, 1760, 476, 2911, 1049, 1074, 849, 272, 248, 204, 3313, 2010, 513, 1939, 1659, 2234, 1038, 251, 
     3053, 1045, 2350, 2892, 1035, 130});

  }
  virtual void TearDown() {
    // Clean up the test cases
  }
};

TEST_F(EncDecUnitTest, TestOfEncodeMethod) {
  EncDecUnit enc_unit = EncDecUnit(256);
  Bytes result = enc_unit.encode_(test_polynomial1, 12);
  std::string expected_result = "41aa8db87c81f5250106318beddb923006d0976ab5f08776b3104580b1c8d980b5ae2560c2132831e09b1f2b20f1ec7664f62e5e396b307b515ea6b4caf443c5444dff07395c1841ef911b18b9cae269c65b05068d2a0b6b5c5907516522933097462ed4e22bafc269229c0a16d3649a423f7b6c2662497b90d2ad4a653dae11897da72a1e72196d03a6eb34c374943e90a8bf894cccd3a73cbf54a30261b2d3322a8127a301334d111a3cdb82080ce038e7162e882221366cae53bb11f073210da28727bc32b2252008f3331c208e04f39c6743972e2bc9ebc65874fb00c01a12d28b9a60b69e45663bf8d1c2c169ac80342615db322c2781563ba958700a56d92d2a9ac33ed5b5429478f39378a0db413a68738eb7aaea30ad60a50a0b02bc1309a7eac4199ce08aaea261e7f1246260b495567dd5d34302409ce3292668e59a018a774b5c766b51cd019a93cc45a27be20966bb6ed0aba5d5198115026edcf1b5192443510311f8c00cf1ac7d0132797ba68b0eb40fed5b412ec9b40b2408";
  EXPECT_EQ(result.FromBytesToHex(), expected_result);
}
