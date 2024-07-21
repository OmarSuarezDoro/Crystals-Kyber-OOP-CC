#include <iostream>

#include "./DataStructures/Polynomial.h"
#include "./DataStructures/Matrix.h"
#include "./Components/Keccak.h"
#include "./Components/NTT.h"


// Bits interpretados de derecha izquierda (como normalmente sería)
// Mientras que los bytes se interpretan de izquierda a derecha
int main() {
  Keccak keccak;
  // NTT miau(256, 3329);
  // std::cout << miau._FirstPrimitiveRoot(512) << std::endl;
  Bytes miau("  ");
  std::cout << miau.BitReverse(2).FromBytesToBits() << std::endl;  // 00000100 0000100
  std::cout << miau.BitReverse(2).FromBytesToNumbers() << std::endl; // 1028
  std::cout << miau.BitReverse(2).FromBytesToHex() << std::endl; // 0404
  
  return 0;
}