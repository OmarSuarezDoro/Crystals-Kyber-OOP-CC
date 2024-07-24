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
  std::vector<int> values = {1, 1, 0, 0, 0, -1, -1, 0, 1, 0, -1, 1, 0, 0, 0, 2, -2, 0, -1, 1, 0, -2, -1, 0, 0, 0, -1, 0, 0, -2, 0, 0, -1, 0, 0, 0, -1, 1, -1, -2, 1, 0, -1, 0, 1, 2, 0, -1, 1, -1, 2, 0, 1, 0, 0, 1, 1, 1, 0, 1, -2, 1, 0, -1, 1, -1, -1, 1, -2, -2, 0, 2, 1, -2, 0, 0, 1, 1, 0, 2, -2, 0, -2, 2, -1, 1, -1, -3, 0, 0, -1, 3, 1, 0, 1, 1, -2, -1, -2, -3, 0, -1, 0, -1, -1, 1, 1, -1, -1, -2, 0, -1, 1, 0, 0, -1, 0, 0, -1, 1, 1, 0, 1, 1, -1, -2, 1, 1};
  miau2.SetCoefficients(values);
  std::cout << miau2.GetSize() << std::endl;
  NTT ntt(128, 3329);
  std::cout << ntt._NTT(miau2) << std::endl;
    
  return 0;
}