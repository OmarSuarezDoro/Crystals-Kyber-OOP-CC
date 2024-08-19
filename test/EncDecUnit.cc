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
  Bytes test_bytes1;
  Bytes test_bytes2;

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
    test_bytes1 = Bytes(std::vector<int>{60, 149, 134, 17, 170, 203, 63, 167, 35, 56, 49, 0, 177, 114, 59, 133, 50, 13, 129, 218, 7, 103, 140, 9, 234,
     124, 9, 32, 0, 80, 176, 198, 106, 181, 166, 91, 204, 182, 53, 236, 197, 73, 116, 129, 179, 72, 160, 178, 72, 249, 118, 41, 231, 107, 167, 233, 112,
     11, 133, 204, 163, 179, 189, 157, 97, 136, 17, 217, 29, 106, 122, 69, 55, 240, 158, 125, 179, 72, 103, 19, 60, 207, 58, 18, 246, 106, 75, 169, 235, 
     6, 47, 140, 145, 227, 194, 74, 17, 145, 42, 215, 247, 93, 202, 18, 20, 20, 166, 96, 242, 162, 111, 218, 181, 46, 238, 101, 162, 162, 216, 27, 119, 
     154, 11, 144, 55, 127, 185, 108, 27, 169, 198, 113, 85, 249, 60, 43, 92, 206, 147, 249, 1, 191, 200, 167, 143, 234, 142, 133, 199, 50, 230, 146, 
     16, 66, 187, 108, 26, 123, 200, 1, 22, 68, 17, 85, 44, 73, 89, 89, 199, 163, 98, 131, 217, 103, 62, 193, 59, 243, 67, 124, 38, 22, 157, 36, 144, 
     128, 218, 249, 130, 124, 8, 145, 235, 188, 95, 192, 182, 192, 244, 72, 118, 13, 228, 61, 92, 188, 80, 39, 17, 83, 141, 10, 141, 143, 91, 129, 32, 
     155, 124, 54, 181, 94, 24, 92, 123, 65, 38, 61, 56, 42, 150, 185, 97, 21, 212, 36, 82, 60, 241, 169, 199, 152, 9, 85, 82, 8, 242, 38, 185, 141, 
     104, 63, 4, 225, 86, 70, 118, 92, 60, 220, 140, 224, 108, 184, 156, 225, 129, 21, 72, 162, 160, 230, 142, 20, 203, 15, 27, 184, 128, 58, 249, 136, 
     130, 52, 198, 205, 92, 46, 71, 82, 181, 43, 176, 177, 18, 216, 140, 90, 123, 163, 55, 247, 98, 103, 197, 20, 129, 228, 174, 201, 50, 130, 52, 96, 
     189, 215, 196, 129, 247, 136, 8, 250, 69, 97, 166, 92, 140, 129, 84, 108, 55, 120, 160, 127, 176, 81, 237, 180, 85, 112, 1, 51, 143, 176, 39, 18, 
     247, 159, 26, 20, 79, 74, 167, 9, 233, 181, 114, 198, 183, 116, 242, 23, 36, 145, 167, 28, 140, 138, 24, 183, 113, 192, 72, 165, 31, 183, 50, 164, 
     89, 72, 12, 17, 58, 124});

    test_bytes2 = Bytes(std::vector<int>{181, 183, 19, 49, 136, 74, 245, 186, 130, 250, 249, 145, 220, 245, 56, 39, 252, 184, 127, 246, 194, 188, 155, 40, 137, 170, 26, 210,
    88, 155, 40, 229, 82, 230, 20, 183, 95, 42, 174, 162, 148, 66, 16, 150, 38, 32, 53, 63, 136, 53, 61, 254, 242, 79, 209, 112, 179, 78, 7, 43, 99, 150, 192, 147, 234,
    107, 248, 250, 82, 102, 246, 114, 27, 12, 176, 200, 25, 126, 61, 119, 197, 141, 28, 205, 13, 85, 45, 97, 160, 129, 108, 43, 103, 113, 4, 31, 37, 66, 167, 172, 227,
    6, 211, 96, 51, 254, 153, 188, 24, 68, 171, 195, 40, 185, 96, 183, 122, 178, 120, 81, 171, 203, 154, 191, 50, 162, 248, 114, 55, 229, 108, 28, 40, 171, 106, 148, 27,
    90, 233, 183, 80, 215, 40, 126, 138, 123, 116, 189, 170, 149, 179, 124, 61, 108, 149, 161, 79, 6, 11, 24, 168, 183, 157, 12, 95, 25, 19, 35, 11, 102, 120, 13, 89, 134,
    168, 252, 33, 109, 124, 152, 59, 138, 31, 116, 6, 40, 30, 229, 70, 119, 117, 106, 140, 227, 101, 223, 65, 124, 75, 251, 207, 13, 117, 199, 212, 0, 78, 228, 72, 113, 66,
    236, 198, 82, 67, 71, 128, 97, 207, 69, 246, 128, 254, 202, 89, 27, 169, 176, 15, 226, 14, 181, 241, 113, 22, 168, 39, 60, 101, 179, 100, 136, 47, 102, 112, 11, 62, 168,
    47, 180, 59, 188, 2, 98, 55, 29, 70, 62, 161, 161, 120, 147, 233, 113, 189, 144, 125, 174, 243, 32, 3, 89, 180, 164, 6, 124, 79, 10, 77, 105, 236, 193, 236, 18, 169, 114,
    246, 141, 106, 40, 164, 225, 137, 70, 47, 43, 191, 218, 140, 83, 125, 26, 152, 93, 186, 13, 79, 7, 178, 153, 160, 28, 40, 60, 6, 237, 185, 63, 91, 243, 68, 208, 86, 156,
    98, 25, 52, 183, 21, 111, 85, 55, 21, 134, 137, 42, 191, 92, 6, 31, 58, 127, 205, 250, 96, 159, 81, 197, 232, 196, 47, 197, 195, 107, 156, 150, 133, 103, 135, 124, 234, 49,
    126, 100, 196, 57, 141, 115, 197, 10, 43, 118, 209, 51, 186, 143, 69, 92, 205, 28, 42, 254, 84, 119, 155, 53, 182, 98, 89, 145, 73, 12, 78, 119, 41, 32, 157, 117, 90, 41, 171,
    102, 123, 193, 106, 19, 28, 68, 32, 128, 116, 28, 139, 50, 122, 23, 105, 124, 193, 14, 103, 97, 178, 147, 40, 83, 200, 197, 85, 245, 231, 192, 208, 232, 5, 104, 188, 8, 46, 178,
    47, 121, 34, 74, 225, 37, 200, 1, 204, 171, 19, 180, 151, 121, 101, 9, 253, 81, 168, 232, 138, 39, 41, 54, 163, 2, 155, 104, 185, 70, 66, 47, 87, 33, 99, 179, 106, 149, 39, 195,
    94, 66, 91, 61, 212, 68, 86, 182, 36, 66, 38, 205, 178, 181, 37, 153, 220, 132, 6, 213, 116, 35, 108, 159, 47, 7, 102, 89, 130, 172, 210, 243, 163, 66, 26, 85, 208, 164, 129, 82,
    82, 199, 166, 17, 200, 73, 169, 46, 94, 246, 156, 214, 57, 35, 5, 197, 106, 32, 180, 21, 164, 182, 195, 152, 156, 78, 194, 124, 176, 12, 232, 201, 98, 250, 166, 218, 17, 136, 198,
    179, 89, 255, 171, 75, 226, 58, 164, 58, 97, 77, 204, 52, 161, 74, 163, 2, 154, 140, 198, 160, 164, 168, 57, 3, 114, 39, 32, 77, 181, 184, 28, 96, 34, 106, 183, 118, 124, 68, 65,
    124, 78, 72, 174, 74, 92, 119, 116, 97, 33, 25, 249, 67, 204, 124, 57, 91, 152, 2, 207, 37, 41, 209, 5, 134, 138, 134, 149, 195, 33, 61, 194, 151, 190, 208, 249, 47, 20, 81, 206,
    62, 195, 97, 130, 129, 87, 166, 210, 180, 69, 165, 55, 117, 87, 92, 73, 115, 56, 105, 210, 7, 37, 101, 167, 66, 33, 157, 203, 113, 83, 159, 166, 115, 64, 1, 120, 223, 144, 132, 3,
    204, 29, 56, 134, 26, 240, 54, 37, 183, 41, 178, 179, 147, 191, 165, 101, 69, 10, 212, 55, 164, 19, 97, 206, 228, 146, 2, 57, 142, 169, 243, 3, 132, 224, 50, 247, 208, 100, 145,
    247, 114, 7, 106, 189, 120, 161, 86, 38, 138, 112, 127, 120, 39, 35, 108, 75, 179, 171, 195, 114, 208, 149, 163, 146, 176, 144, 214, 110, 224, 43, 158, 215, 71, 194, 226, 25, 49,
    222, 44, 79, 67, 24, 80, 82, 60, 197, 105, 71, 55, 238, 211, 34, 85, 92, 206, 144, 102, 41, 124, 127, 181, 64, 34, 10, 148, 41, 192, 128, 3, 86, 20, 201, 129, 171, 173, 20, 73, 24,
    83, 6, 155});
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

TEST_F(EncDecUnitTest, TestOfDecodeMethod) {
  EncDecUnit enc_unit = EncDecUnit(256);
  Polynomial<int> result = enc_unit.decode_(test_bytes1, 12);
  Polynomial<int> expected_result = Polynomial<int>(256);
  expected_result.SetCoefficients({{1340, 2153, 2577, 3258, 1855, 570, 312, 3, 689, 951, 645, 211, 2689, 125, 3175, 152, 3306, 151, 32, 1280, 1712, 
    1708, 1717, 1466, 1740, 859, 1516, 1180, 372, 2872, 72, 2858, 2376, 1903, 1833, 1726, 2471, 1806, 1291, 3272, 931, 3035, 413, 2182, 2321, 477, 2666,
    1111, 55, 2543, 893, 1163, 871, 961, 2767, 291, 2806, 1206, 2985, 110, 3119, 2328, 739, 1196, 273, 681, 2007, 1503, 714, 321, 1556, 1546, 754, 1786,
    1498, 747, 1518, 2598, 2210, 445, 2679, 185, 1936, 2035, 3257, 438, 1705, 1820, 2389, 975, 3115, 3301, 2451, 31, 2239, 2684, 2703, 2286, 1925, 812,
    742, 265, 2882, 1739, 2842, 3207, 1537, 1089, 1297, 709, 2377, 1429, 967, 1578, 2435, 1661, 318, 956, 1011, 1988, 1574, 2513, 36, 2057, 2522, 2095,
    2172, 2320, 3307, 1531, 1728, 3083, 2292, 1892, 1037, 990, 3164, 1291, 295, 1329, 2701, 2256, 2959, 2069, 2848, 1993, 1334, 1515, 3096, 1973, 1601, 
    978, 2616, 2402, 441, 342, 1236, 1314, 316, 2719, 2247, 153, 597, 133, 1778, 2962, 2189, 1014, 260, 1390, 1606, 1479, 3132, 2253, 3296, 2950, 412, 
    2078, 2069, 2596, 1696, 2286, 2836, 252, 2075, 2059, 2362, 2191, 1154, 3171, 3277, 741, 583, 2901, 43, 2843, 2066, 2253, 2906, 2615, 1847, 1583, 1383, 
    332, 1153, 2798, 713, 2083, 52, 3030, 1239, 2076, 2295, 136, 1530, 1556, 3238, 2245, 1153, 1733, 2103, 2567, 127, 1307, 1261, 1371, 368, 816, 143, 635, 
    1810, 2559, 1050, 1265, 1866, 154, 1513, 1835, 1990, 1867, 2034, 577, 1937, 458, 2700, 392, 439, 3079, 1352, 506, 695, 2627, 2137, 196, 2577, 1987}});
  EXPECT_EQ(result.GetCoefficients(), expected_result.GetCoefficients());
}


TEST_F(EncDecUnitTest, TestOfDecodeMatrixMethod) {
  EncDecUnit enc_unit = EncDecUnit(256);
  Matrix<Polynomial<int>> result = enc_unit.DecodeBytesToMatrix(test_bytes1, 1, 2, 12);
  // Polynomial<int> expected_result = Polynomial<int>(256);
  // expected_result.SetCoefficients({});
  
  EXPECT_EQ(result.GetCoefficients(), expected_result.GetCoefficients());
}