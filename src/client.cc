#include <iostream>

#include "./DataStructures/Polynomial.h"
#include "./DataStructures/Matrix.h"
#include "./Components/Keccak.h"

int main() {
  std::cout << "Hello World!" << std::endl;
  Matrix<Polynomial<int>> mat(2, 2, 3);
  std::cout << mat << std::endl;
  mat(0, 0)[0] = 1;
  mat(0, 0)[1] = 2;
  mat(0, 0)[2] = 3;
  mat(0, 1)[0] = 4;

  Matrix<Polynomial<int>> mat2(2, 2, 3);
  mat2(0, 0)[0] = 552;

  std::cout << mat + mat2 << std::endl;
  return 0;
}