#include <gtest/gtest.h>
#include <iostream>

GTEST_API_ int main(int argc, char **argv) {
	std::cout << "Executing main() of gtest_main.cc\n";
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}