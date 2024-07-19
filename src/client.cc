#include <iostream>

#include "./DataStructures/Polynomial.h"
#include "./DataStructures/Matrix.h"
#include "./Components/Keccak.h"

int main() {
  Keccak keccak;
  Bytes miau("Hello World");
  // Bytes bytes = keccak.XOF(miau, miau, miau, 32);
  // Bytes bytes = keccak.H(miau, 32);
  // Bytes bytes = keccak.PRF(miau, 128, 32);
  // Bytes bytes = keccak.KDF(miau, 32);
  Bytes bytes = keccak.G(miau)[0];
  Bytes bytes2 = keccak.G(miau)[1];

  std::cout << bytes.FromBytesToHex() << std::endl; 
  std::cout << bytes2.FromBytesToHex() << std::endl; 
  return 0;
}