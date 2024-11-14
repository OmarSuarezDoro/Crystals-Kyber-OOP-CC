/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date August 20 2024
 * @version v0.1.0
 * @brief This file contains the tests for the CompressorUnit class
 */

#include <gtest/gtest.h>
#include "../src/Components/CompressorUnit.h"
#include "../src/DataStructures/Bytes.h"

class CompressorUnitTest : public ::testing::Test {
 public:
  Polynomial<int> test_polynomial1 = Polynomial<int>(256);
  Polynomial<int> test_polynomial2 = Polynomial<int>(256);


 protected:
  virtual void SetUp() {
    // Set up the test cases
   test_polynomial1.SetCoefficients({2985, 2793, 2816, 1537, 1981, 1189, 3288, 1053, 1578, 972, 2640, 666, 838, 2034, 3115,
   2590, 873, 530, 1845, 3004, 2526, 3166, 2141, 661, 1826, 2171, 2006, 2912, 172, 961, 609, 2326, 1287, 1904, 567, 2478, 1149,
   1560, 2402, 1800, 1982, 2310, 2327, 720, 2702, 2140, 622, 286, 2676, 2427, 1057, 2473, 199, 1376, 2601, 1017, 1391, 2157, 1761,
   104, 149, 770, 368, 2476, 1852, 1952, 567, 2417, 2998, 1706, 2379, 3036, 1309, 2089, 3296, 2301, 420, 1037, 3312, 176, 698, 1599,
   946, 2842, 1014, 650, 21, 3166, 1134, 1212, 2602, 3321, 264, 1570, 808, 1145, 1617, 1615, 306, 2885, 1435, 830, 1825, 1966, 1601,
   484, 2467, 3213, 2993, 1230, 2361, 190, 2636, 3004, 1592, 2407, 2818, 2030, 1974, 2989, 1737, 213, 1779, 2244, 1740, 207, 1666, 357,
   900, 1850, 936, 3060, 3143, 1985, 2369, 982, 2513, 2699, 1918, 2831, 1224, 2390, 8, 1864, 2194, 680, 886, 2663, 1640, 1489, 2621, 177,
   1431, 3001, 2661, 2929, 857, 308, 557, 2004, 869, 3281, 1985, 621, 650, 971, 1475, 3290, 764, 3199, 2763, 1868, 847, 1245, 2180, 2010,
   93, 2080, 1574, 1600, 448, 1821, 1317, 1706, 231, 1313, 3150, 1764, 993, 2325, 2361, 3169, 1003, 2827, 2301, 853, 2603, 56, 839, 2392,
   3138, 2689, 867, 1852, 1450, 1242, 2409, 2526, 845, 1276, 1721, 2575, 1242, 1741, 2753, 1671, 1779, 3220, 2489, 2340, 3290, 1623, 2762,
   1207, 1941, 2928, 1434, 1160, 1617, 1813, 719, 957, 958, 732, 2393, 2413, 3011, 3037, 2233, 2311, 3128, 1562, 2743, 3075, 1323, 1992, 2755,
   727, 3104, 648, 3016, 2509, 2721, 2720, 2447, 1927});
   test_polynomial2.SetCoefficients({1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1,
   1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0,
   1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 
   0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 
   0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 
   0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0});
  
  }
  virtual void TearDown() {
    // Clean up the test cases
  }
};

TEST_F(CompressorUnitTest, TestOfCompressMethod) {
  CompressorUnit comp_unit = CompressorUnit(3329);
  Polynomial<int> result = comp_unit.Compress_(test_polynomial1, 10);
  Polynomial<int> expected_result = Polynomial<int>(256);
  expected_result.SetCoefficients({918, 859, 866, 473, 609, 366, 1011, 324, 485, 299, 812, 205, 258, 626, 958, 797, 269, 163, 568, 924, 777, 974, 659, 203, 562,
  668, 617, 896, 53, 296, 187, 715, 396, 586, 174, 762, 353, 480, 739, 554, 610, 711, 716, 221, 831, 658, 191, 88, 823, 747, 325, 761, 61, 423, 800, 313, 428, 663,
  542, 32, 46, 237, 113, 762, 570, 600, 174, 743, 922, 525, 732, 934, 403, 643, 1014, 708, 129, 319, 1019, 54, 215, 492, 291, 874, 312, 200, 6, 974, 349, 373, 800,
  1022, 81, 483, 249, 352, 497, 497, 94, 887, 441, 255, 561, 605, 492, 149, 759, 988, 921, 378, 726, 58, 811, 924, 490, 740, 867, 624, 607, 919, 534, 66, 547, 690,
  535, 64, 512, 110, 277, 569, 288, 941, 967, 611, 729, 302, 773, 830, 590, 871, 377, 735, 2, 573, 675, 209, 273, 819, 504, 458, 806, 54, 440, 923, 819, 901, 264,
  95, 171, 616, 267, 1009, 611, 191, 200, 299, 454, 1012, 235, 984, 850, 575, 261, 383, 671, 618, 29, 640, 484, 492, 138, 560, 405, 525, 71, 404, 969, 543, 305, 715,
  726, 975, 309, 870, 708, 262, 801, 17, 258, 736, 965, 827, 267, 570, 446, 382, 741, 777, 260, 392, 529, 792, 382, 536, 847, 514, 547, 990, 766, 720, 1012, 499, 850,
  371, 597, 901, 441, 357, 497, 558, 221, 294, 295, 225, 736, 742, 926, 934, 687, 711, 962, 480, 844, 946, 407, 613, 847, 224, 955, 199, 928, 772, 837, 837, 753, 593});
  EXPECT_EQ(result.GetCoefficients(), expected_result.GetCoefficients());
}

TEST_F(CompressorUnitTest, TestOfDecompressMethod) {
  CompressorUnit comp_unit = CompressorUnit(3329);
  Polynomial<int> result = comp_unit.Decompress_(test_polynomial2, 1);
  Polynomial<int> expected_result = Polynomial<int>(256);
  expected_result.SetCoefficients({1665, 0, 1665, 1665, 0, 0, 1665, 0, 1665, 0, 0, 1665, 0, 1665, 1665, 0, 0, 0, 0, 0, 0, 1665, 0, 0, 0, 1665, 1665, 1665, 0, 1665, 1665,
  0, 1665, 1665, 1665, 1665, 0, 1665, 1665, 0, 1665, 0, 1665, 1665, 0, 1665, 1665, 0, 0, 1665, 0, 0, 0, 1665, 1665, 0, 0, 1665, 0, 0, 1665, 1665, 1665, 0, 1665, 0, 1665,
  0, 0, 1665, 1665, 0, 0, 0, 0, 0, 0, 1665, 0, 0, 1665, 0, 1665, 0, 0, 1665, 1665, 0, 1665, 1665, 0, 0, 1665, 1665, 1665, 0, 0, 0, 0, 0, 0, 1665, 0, 0, 1665, 0, 1665,
  1665, 0, 0, 1665, 0, 1665, 0, 0, 0, 0, 1665, 1665, 0, 0, 1665, 1665, 1665, 0, 1665, 1665, 0, 1665, 0, 1665, 0, 1665, 1665, 1665, 0, 1665, 0, 1665, 0, 0, 1665, 1665,
  0, 0, 0, 1665, 1665, 0, 1665, 1665, 0, 1665, 0, 0, 0, 0, 1665, 0, 0, 0, 0, 1665, 1665, 0, 0, 0, 0, 0, 0, 1665, 1665, 0, 0, 0, 0, 0, 0, 1665, 1665, 0, 0, 0, 0, 0, 0,
  1665, 1665, 0, 0, 0, 0, 0, 0, 1665, 1665, 0, 0, 0, 0, 0, 0, 1665, 1665, 0, 0, 0, 0, 0, 0, 1665, 1665, 0, 0, 0, 0, 0, 0, 1665, 1665, 0, 0, 0, 0, 0, 0, 1665, 1665, 0,
  0, 0, 0, 0, 0, 1665, 1665, 0, 0, 0, 0, 0, 0, 1665, 1665, 0, 0, 0, 0, 0, 0, 1665, 1665, 0, 0, 0, 0});
  EXPECT_EQ(result.GetCoefficients(), expected_result.GetCoefficients());
}