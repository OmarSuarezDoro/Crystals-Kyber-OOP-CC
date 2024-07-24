/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date July 18 2024
 * @version v0.1.0
 * @brief This file contains the tests for the NTT class
 */

#include <gtest/gtest.h>
#include "../src/Components/NTT.h"
#include "../src/DataStructures/Polynomial.h"

class NTTTest : public ::testing::Test {
 public:
  NTT ntt_ = NTT(128, 3329);
  Polynomial<int> test_polynomial1 = Polynomial<int>(128);
  Polynomial<int> test_polynomial2 = Polynomial<int>(128);
  Polynomial<int> test_polynomial3 = Polynomial<int>(128);
 protected:
  virtual void SetUp() {
    // Set up the test cases
    test_polynomial1.SetCoefficients({1, 1, 0, 0, 0, -1, -1, 0, 1, 0, -1, 1, 0, 0, 0, 2, -2, 0, -1, 1, 0, 
    -2, -1, 0, 0, 0, -1, 0, 0, -2, 0, 0, -1, 0, 0, 0, -1, 1, -1, -2, 1, 0, -1, 0, 1, 2, 0, -1, 
    1, -1, 2, 0, 1, 0, 0, 1, 1, 1, 0, 1, -2, 1, 0, -1, 1, -1, -1, 1, -2, -2, 0, 2, 1, -2, 0, 0, 
    1, 1, 0, 2, -2, 0, -2, 2, -1, 1, -1, -3, 0, 0, -1, 3, 1, 0, 1, 1, -2, -1, -2, -3, 0, -1, 0, 
    -1, -1, 1, 1, -1, -1, -2, 0, -1, 1, 0, 0, -1, 0, 0, -1, 1, 1, 0, 1, 1, -1, -2, 1, 1});
    test_polynomial2.SetCoefficients({-1, -1, 1, 0, 1, 1, 0, -2, 0, 0, 2, 1, 1, 2, -1, -1, 1, -1,
    0, -1, 1, 1, 0, 1, 0, -1, 0, -2, -1, 1, 1, 0, -2, -2, 2, 1, 1, 1, 1, 0, 3, 1, -3, -3, 0, 1, 
    -1, -1, -2, -2, 1, -1, 0, 1, -1, 0, 3, -2, 0, 1, 0, 1, -1, -1, 1, -1, 1, 1, 1, -1, -1, 0, 1,
    2, 1, 1, 1, -1, 0, -1, 0, -1, 3, 0, -2, 2, 2, -2, 2, -1, 0, -1, 0, 1, 2, 1, -1, -1, 1, -1, 0, 
    2, 1, -3, 2, 1, -2, 1, 0, 2, 0, 2, 0, 0, 0, -1, -1, 1, -3, -1, -1, 1, 0, 0, 2, -2, 1, 0});
    test_polynomial3.SetCoefficients({2, -1, -2, 3, -1, 1, -1, 1, 0, 0, 0, 3, 0, 0, 1, 0, 1, 1, 0, -1, 1, 0, 
    -1, -1, 2, 1, 1, 2, 0, -1, -2, 0, 0, -1, -3, -2, 0, 2, 1, 1, -1, 0, -1, 3, 0, 0, 0, -1, 0, 1, 0, 0, 0, -1, 
    -1, 0, -3, 0, 0, 0, 0, -1, 0, -1, -2, -2, 2, 1, 1, 2, 1, 0, 1, -1, 0, 1, -1, 0, -1, -1, 0, -1, 0, -3, -3, 
    -1, 0, -1, 1, -1, 2, 1, 0, 0, 1, 1, 1, 0, 0, -1, 2, -1, 1, 2, 0, 1, 1, -1, 1, 2, -1, 0, -1, -2, -2, -1, 0, 
    2, 0, 1, 1, 0, 1, 3, 1, -1, 0, 0});
  }
  virtual void TearDown() {
    // Clean up the test cases
  }
};

/**
 * @brief Test for NTT
 * 
 */
TEST_F(NTTTest, NTTTEST0) {
  Polynomial<int> result = ntt_._NTT(test_polynomial1);
  std::vector<int> expected_values = {1139, 1156, 67, 3323, 3208, 1870, 416, 3121, 1746, 3191, 1485, 755, 494, 690, 1278, 2827, 950, 1098, 1201, 2788, 1761, 424, 2971, 1754, 2424, 2703, 2724, 2554, 1384, 1871, 510, 1373, 713, 1733, 1942, 2134, 1881, 783, 1217, 3249, 3310, 141, 1380, 51, 1033, 846, 691, 1242, 1206, 2590, 2335, 3086, 927, 1595, 2145, 188, 1869, 1113, 539, 2184, 2870, 768, 2581, 464, 1856, 736, 1574, 681, 937, 2096, 1719, 3076, 1978, 2858, 2671, 1352, 264, 2884, 1750, 1309, 2304, 915, 1596, 830, 991, 1303, 2805, 1791, 2833, 649, 2588, 1257, 2454, 1920, 1192, 673, 2877, 1339, 2614, 442, 1483, 1494, 2255, 2748, 2172, 2902, 1377, 1157, 2179, 1213, 2188, 331, 664, 2765, 2056, 2394, 731, 3025, 2066, 772, 426, 1086, 2200, 2778, 2144, 1555, 2941, 2235};
  Polynomial<int> expected_polynomial = Polynomial<int>(128);
  expected_polynomial.SetCoefficients(expected_values);
  EXPECT_EQ(result, expected_polynomial);
}

/**
 * @brief Test for NTT
 * 
 */
TEST_F(NTTTest, NTTTEST1) {
  Polynomial<int> result = ntt_._NTT(test_polynomial2);
  std::vector<int> expected_values = {2456, 470, 2557, 2506, 1018, 3122, 397, 2416, 858, 2701, 2109, 3231, 607, 2298, 
  2060, 1689, 1027, 258, 2167, 73, 1624, 616, 2593, 2689, 573, 439, 2173, 1619, 2181, 1471, 874, 376, 3181, 2348, 1673, 
  981, 1567, 3280, 2500, 274, 2025, 1576, 2532, 282, 23, 3107, 372, 1219, 3100, 3294, 1006, 748, 2059, 1561, 1520, 1615, 
  1849, 3027, 731, 1415, 88, 371, 1327, 2035, 1786, 1938, 195, 1760, 1396, 1363, 154, 2651, 1291, 1399, 1394, 2402, 2062, 
  1454, 2240, 428, 947, 685, 2830, 807, 3216, 1458, 2065, 48, 2104, 428, 600, 185, 1599, 196, 896, 2429, 27, 117, 1434, 
  345, 718, 1340, 1483, 9, 1559, 1389, 448, 2792, 3016, 2172, 1403, 792, 1377, 1124, 3038, 2452, 135, 2144, 499, 253, 1318, 
  913, 1432, 1988, 230, 1180, 751, 78};
  Polynomial<int> expected_polynomial = Polynomial<int>(128);
  expected_polynomial.SetCoefficients(expected_values);
  EXPECT_EQ(result, expected_polynomial);
}

/**
 * @brief Test for NTT
 * 
 */
TEST_F (NTTTest, NTTTEST2) {
  Polynomial<int> result = ntt_._NTT(test_polynomial3);
  std::vector<int> expected_values = {765, 1130, 2610, 2855, 439, 3253, 2149, 1366, 618, 3261, 2892, 76, 139, 2074, 1118, 
  1287, 1977, 2511, 2021, 328, 686, 2071, 2461, 601, 1877, 1744, 877, 2648, 1146, 1490, 560, 2219, 3023, 666, 2852, 713, 
  2370, 339, 3019, 488, 3194, 521, 2097, 520, 2616, 2631, 3159, 63, 2212, 2000, 519, 2596, 1297, 3192, 303, 1024, 1663, 
  3152, 393, 2019, 2163, 2063, 1128, 3143, 1102, 1240, 629, 387, 1293, 1508, 1370, 1165, 586, 2550, 156, 3046, 2664, 3182, 
  3317, 2834, 2304, 1001, 2103, 1193, 526, 1629, 2956, 749, 1805, 868, 2629, 1964, 2018, 978, 1467, 2243, 2122, 507, 3125, 
  1756, 3244, 613, 746, 1763, 2228, 262, 1831, 1576, 230, 2585, 1839, 897, 3110, 1212, 1912, 2574, 1447, 2989, 2679, 625, 
  697, 1624, 2688, 1433, 1140, 2693, 2179, 466};
  Polynomial<int> expected_polynomial = Polynomial<int>(128);
  expected_polynomial.SetCoefficients(expected_values);
  EXPECT_EQ(result, expected_polynomial);
}
