#include <iostream>

#include "./DataStructures/Polynomial.h"
#include "./DataStructures/Matrix.h"
#include "./Components/Keccak.h"
#include "./Components/NTT.h"
#include "./Components/SamplingUnit.h"

// Bits interpretados de derecha izquierda (como normalmente sería)
// Mientras que los bytes se interpretan de izquierda a derecha
int main() {
  std::vector<int> input_vector_;
  SamplingUnit sampling_unit = SamplingUnit(2, 256);
  input_vector_ = std::vector<int>{176 ,216 ,234 ,235 ,78 ,216 ,233 ,120 ,200 ,68 ,123 ,63 ,178 ,112 ,49 ,17 ,28 ,49 ,51 ,213 ,3 ,17 ,219 ,92 ,223 ,193 ,6 ,184 ,167 ,217 ,201 ,241};
  Bytes input_bytes = Bytes(input_vector_);
  Matrix<Polynomial<int>> result_poly = sampling_unit.GenerateDistribuitionMatrix(input_bytes, 3, 0);
  return 0;
}