#include <iostream>

#include "./DataStructures/Polynomial.h"
#include "./DataStructures/Matrix.h"
#include "./Components/Keccak.h"
#include "./Components/NTT.h"


// Bits interpretados de derecha izquierda (como normalmente sería)
// Mientras que los bytes se interpretan de izquierda a derecha
int main() {
  // Keccak keccak;
  // NTT miau(256, 3329);
  // std::cout << miau._FirstPrimitiveRoot(512) << std::endl;
  // Bytes miau("  ");
  // std::cout << miau.BitReverse(2).FromBytesToBits() << std::endl;  // 00000100 0000100
  // std::cout << miau.BitReverse(2).FromBytesToNumbers() << std::endl; // 1028
  // std::cout << miau.BitReverse(2).FromBytesToHex() << std::endl; // 0404
  Polynomial<int> miau2(128);
  std::vector<int> values = {733, 1883, 2580, 1261, 3075, 1244, 1671, 2183, 424, 2371, 390, 2712, 2941, 3049, 1698, 2260, 1665, 3237, 1031, 497, 161, 2268, 2604, 3065, 565, 1391, 2987, 136, 240, 2417, 749, 729, 2727, 2073, 2646, 3012, 1431, 974, 1792, 865, 3172, 614, 1054, 1929, 2496, 581, 1270, 3007, 205, 1255, 717, 3131, 848, 132, 2599, 1601, 2728, 1962, 225, 2309, 1872, 310, 1907, 1989, 989, 2140, 1420, 2752, 1112, 705, 1556, 2947, 1401, 2620, 458, 1032, 149, 627, 2634, 2818, 1276, 2905, 639, 869, 2242, 183, 3154, 3296, 2853, 2222, 2392, 1924, 3009, 425, 2676, 1351, 1869, 2540, 666, 2911, 1135, 631, 539, 2010, 3112, 2102, 3284, 1901, 2074, 3121, 2392, 2845, 316, 1277, 326, 1437, 220, 39, 1595, 2072, 1621, 2748, 2020, 2879, 3272, 2265, 2857, 1990};
  miau2.SetCoefficients(values);
  std::cout << miau2.GetSize() << std::endl;
  NTT ntt(128, 3329);
  std::cout << ntt._INTT(miau2) << std::endl;
    
  return 0;
}