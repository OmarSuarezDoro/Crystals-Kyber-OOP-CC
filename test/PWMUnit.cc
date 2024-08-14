/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date August 14 2024
 * @version v0.1.0
 * @brief This file contains the tests for the PWMUnit class
 */

#include <gtest/gtest.h>
#include "../src/Components/PWMUnit.h"

class PWMUnitTest : public ::testing::Test {
 public:
  Polynomial<int> test_polynomial1 = Polynomial<int>(256);
  Polynomial<int> test_polynomial2 = Polynomial<int>(256);

 protected:
  virtual void SetUp() {
    // Set up the test cases
    test_polynomial1.SetCoefficients({2979, 1930, 539, 812, 3217, 2526, 949, 1728, 3244, 1603, 74, 972, 
    674, 2156, 889, 1691, 1089, 335, 2035, 2924, 313, 1410, 3294, 805, 1054, 2227, 1197, 255, 702, 2525, 
    86, 2580, 1282, 153, 1339, 2608, 479, 1502, 3087, 1680, 1235, 247, 1034, 1685, 863, 1386, 1475, 1645, 
    2539, 2532, 1047, 546, 2097, 3152, 1451, 2126, 784, 747, 2759, 1785, 1368, 846, 17, 2187, 1337, 1766, 
    1562, 1792, 1497, 2104, 1000, 2198, 1551, 2612, 2461, 3087, 1366, 2187, 1586, 1754, 409, 1777, 3035, 
    922, 2408, 2645, 2031, 2240, 1651, 296, 3240, 1767, 3105, 1180, 435, 1538, 807, 1740, 2575, 121, 184, 
    1478, 1984, 3035, 2520, 1528, 8, 2013, 2212, 663, 2885, 2365, 712, 2967, 1850, 2348, 670, 2016, 1165, 
    3030, 1104, 1222, 3199, 3251, 2297, 2403, 1711, 457, 1204, 596, 3269, 648, 1813, 1031, 469, 1572, 1863, 
    953, 2729, 2099, 403, 605, 1760, 982, 2830, 241, 1147, 2974, 1980, 1923, 1347, 970, 399, 988, 1867, 2070, 
    195, 971, 525, 1909, 2578, 1305, 2220, 2187, 972, 2445, 889, 455, 188, 2644, 1729, 997, 2942, 2197, 2870, 
    711, 153, 2400, 348, 290, 2304, 2541, 721, 3244, 2878, 1871, 386, 177, 2941, 2797, 2055, 602, 2975, 2881, 
    2091, 1260, 3268, 1228, 1806, 2398, 2685, 1107, 1405, 2564, 71, 1705, 653, 2235, 2161, 1436, 2852, 2067, 
    1215, 2204, 2396, 3018, 3057, 1290, 653, 308, 2002, 2656, 831, 2172, 2375, 1213, 104, 2445, 2297, 211, 487, 
    3077, 2512, 2849, 3050, 3184, 2975, 582, 401, 3155, 1212, 560, 2234, 397, 1609, 1855, 1428, 477, 2786, 2918, 
    2493, 905, 1466, 2752, 318, 3131});
    test_polynomial2.SetCoefficients({2955, 2017, 688, 2337, 1143, 2104, 120, 3252, 1947, 666, 192, 564, 1404, 2258, 
    2755, 753, 39, 1816, 1138, 3245, 479, 201, 265, 2555, 1467, 1091, 34, 852, 1414, 494, 2324, 2131, 1357, 2972, 1822, 
    3246, 3047, 452, 1063, 2688, 907, 797, 889, 2363, 27, 109, 2901, 1639, 3214, 3063, 3069, 875, 3227, 328, 1724, 1221, 
    2569, 1901, 2506, 1306, 960, 1898, 2307, 788, 2847, 1919, 2417, 1202, 2386, 1805, 2574, 2518, 1559, 2331, 2300, 1529, 
    1278, 1621, 1569, 2111, 2261, 1145, 2270, 1762, 1289, 2271, 1760, 2880, 1386, 3072, 506, 3093, 719, 1657, 2733, 1849, 
    2022, 558, 2000, 2118, 2957, 605, 376, 973, 2960, 3115, 1339, 2227, 1523, 1400, 1171, 1548, 1519, 2911, 2023, 1376, 898, 
    2692, 1085, 1496, 3170, 2129, 2172, 1045, 2627, 2117, 2144, 334, 429, 2112, 2165, 66, 2266, 863, 1198, 1174, 2307, 1809, 
    1397, 1928, 733, 1311, 3014, 2014, 1847, 1554, 156, 827, 2204, 2677, 993, 3, 1613, 813, 705, 1768, 3250, 2774, 80, 1368, 
    2943, 1137, 662, 2561, 1944, 1553, 3251, 976, 1740, 2945, 300, 2144, 1022, 2017, 3241, 2589, 2720, 567, 1062, 1612, 43, 
    2808, 1398, 2997, 99, 2437, 319, 18, 58, 1162, 3310, 2514, 2662, 3102, 1289, 2167, 2642, 740, 2107, 1474, 2609, 2627, 1231, 
    2788, 2220, 2105, 1370, 2197, 1433, 1947, 2047, 304, 1335, 660, 3225, 2617, 1347, 2506, 1877, 1793, 2058, 3106, 1807, 1795, 
    628, 774, 2259, 2869, 1186, 1446, 2880, 2204, 612, 84, 2263, 689, 2803, 3152, 442, 3088, 2694, 218, 2091, 171, 1330, 2817, 
    1474, 995, 380, 2375, 365, 2544, 3135, 1328, 2194, 1744});
  }
  virtual void TearDown() {
    // Clean up the test cases
  }
};

TEST_F(PWMUnitTest, PointwiseMultTest1) {
  PWMUnit pwm_unit = PWMUnit(256, 3329);
  Polynomial<int> result = pwm_unit.pointwise_(test_polynomial1, test_polynomial2);
  std::vector<int> expected_values = {1648, 371, 2704, 665, 459, 1686, 3173, 1127, 775, 1751, 2931, 1988, 3084, 1502, 2436, 1722, 
  848, 3276, 2276, 680, 2273, 2594, 42, 727, 2955, 2669, 2808, 3182, 1617, 2234, 3108, 562, 769, 2951, 955, 13, 2997, 2671, 1812, 
  155, 71, 3226, 1972, 3100, 2723, 1658, 2698, 2359, 3103, 2185, 1613, 1837, 826, 122, 2360, 638, 1540, 531, 2496, 310, 2639, 3057, 
  1467, 2054, 2624, 56, 603, 203, 534, 2278, 1221, 2957, 2532, 828, 1189, 442, 2521, 2456, 2872, 1344, 667, 1939, 2888, 295, 478, 
  2859, 2412, 1091, 2065, 2594, 2498, 2960, 1162, 1205, 2097, 853, 1168, 418, 1747, 3260, 1734, 932, 801, 2254, 2111, 2116, 1546, 
  88, 116, 1892, 241, 1478, 1938, 1401, 3151, 1765, 2487, 2043, 2505, 271, 809, 2255, 387, 1002, 505, 3306, 1507, 3297, 2416, 
  2172, 569, 780, 840, 2606, 2073, 363, 2554, 2650, 1971, 1146, 2682, 3059, 22, 2851, 2707, 2581, 182, 1017, 151, 1167, 2064, 
  1841, 2969, 527, 3033, 3065, 1899, 1490, 2823, 2051, 163, 615, 776, 2496, 2174, 747, 1313, 3253, 266, 928, 894, 1289, 1729, 
  3324, 206, 785, 616, 28, 2261, 87, 3094, 791, 575, 1330, 1752, 1617, 3054, 160, 816, 993, 1778, 1540, 3190, 2997, 1909, 16, 
  2563, 67, 2551, 1337, 3011, 1264, 438, 2628, 747, 3006, 1892, 2441, 1788, 77, 2775, 1458, 1146, 2444, 1981, 879, 595, 705, 
  2027, 1220, 1890, 2799, 184, 166, 1609, 65, 3002, 2539, 943, 3020, 1786, 1372, 1308, 473, 143, 2287, 392, 2872, 1217, 2888, 
  146, 1828, 2678, 385, 1960, 2145, 2666, 56, 1604, 2310, 2326, 1201, 1337, 1464, 2180, 336};
  Polynomial<int> expected_polynomial = Polynomial<int>(128);
  expected_polynomial.SetCoefficients(expected_values);
  EXPECT_EQ(result, expected_polynomial);
}
