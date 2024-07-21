/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Trabajo de Fin de Grado - Kleptographic Attacks on Lattice-Based CryptoSystems
 *
 * @author Omar Suárez Doro
 * @date July 18 2024
 * @version v0.1.0
 * @brief This file contains the tests for the Bytes class
 */

#include <gtest/gtest.h>
#include "../src/DataStructures/Bytes.h"

class BytesTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    // Set up the test cases
  }
  
  virtual void TearDown() {
    // Clean up the test cases
  }
};

/**
 * @brief Test for the default constructor.
 */
TEST_F(BytesTest, DefaultConstructorTest) {
  Bytes bytes;
  EXPECT_EQ(bytes.GetBytes(), "\0");
}

/**
 * @brief Test for the parameterized constructor with std::string.
 */
TEST_F(BytesTest, ParameterizedConstructorTest) {
  Bytes bytes("test");
  EXPECT_EQ(bytes.GetBytes(), "test");
}

/**
 * @brief Test for the copy constructor.
 */
TEST_F(BytesTest, CopyConstructorTest) {
  Bytes bytes1("copy");
  Bytes bytes2(bytes1);
  EXPECT_EQ(bytes2.GetBytes(), "copy");
}

/**
 * @brief Test for the parameterized constructor with uint8_t.
 */
TEST_F(BytesTest, ParameterizedConstructorWithByteTest) {
  uint8_t byte = 'A';
  Bytes bytes(byte);
  EXPECT_EQ(bytes.GetBytes(), "A");
}

/**
 * @brief Test for the destructor.
 */
TEST_F(BytesTest, DestructorTest) {
  Bytes* bytes = new Bytes("destruct");
  delete bytes;
  // Since there's no way to check the destructor directly,
  // we just ensure that no errors occur during deletion.
}

/**
 * @brief Test for the operator+ method.
 */
TEST_F(BytesTest, AdditionOperatorTest) {
  Bytes bytes1("hello");
  Bytes bytes2("world");
  Bytes result = bytes1 + bytes2;
  EXPECT_EQ(result.GetBytes(), "helloworld");
}

/**
 * @brief Test for the operator^ method.
 */
TEST_F(BytesTest, XorOperatorTest) {
  Bytes bytes1("abc");
  Bytes bytes2("def");
  Bytes result = bytes1 ^ bytes2;
  std::string expected_result = std::string(1, 'a' ^ 'd') + std::string(1, 'b' ^ 'e') + std::string(1, 'c' ^ 'f');
  EXPECT_EQ(result.GetBytes(), expected_result);
}

/**
 * @brief Test for the operator| method.
 */
TEST_F(BytesTest, OrOperatorTest) {
  Bytes bytes1("abc");
  Bytes bytes2("def");
  Bytes result = bytes1 | bytes2;
  std::string expected_result = std::string(1, 'a' | 'd') + std::string(1, 'b' | 'e') + std::string(1, 'c' | 'f');
  EXPECT_EQ(result.GetBytes(), expected_result);
}

/**
 * @brief Test for the operator& method.
 */
TEST_F(BytesTest, AndOperatorTest) {
  Bytes bytes1("abc");
  Bytes bytes2("def");
  Bytes result = bytes1 & bytes2;
  std::string expected_result = std::string(1, 'a' & 'd') + std::string(1, 'b' & 'e') + std::string(1, 'c' & 'f');
  EXPECT_EQ(result.GetBytes(), expected_result);
}

/**
 * @brief Test for the operator<< method.
 */
TEST_F(BytesTest, LeftShiftOperatorTest) {
  Bytes bytes("abc");
  Bytes result = bytes << 1;
  std::string expected_result = std::string(1, 'a' << 1) + std::string(1, 'b' << 1) + std::string(1, 'c' << 1);
  EXPECT_EQ(result.GetBytes(), expected_result);
}

/**
 * @brief Test for the operator>> method.
 */
TEST_F(BytesTest, RightShiftOperatorTest) {
  Bytes bytes("abc");
  Bytes result = bytes >> 1;
  std::string expected_result = std::string(1, 'a' >> 1) + std::string(1, 'b' >> 1) + std::string(1, 'c' >> 1);
  EXPECT_EQ(result.GetBytes(), expected_result);
}

/**
 * @brief Test for the operator~ method.
 */
TEST_F(BytesTest, NotOperatorTest) {
  Bytes bytes("abc");
  Bytes result = ~bytes;
  std::string expected_result = std::string(1, ~'a') + std::string(1, ~'b') + std::string(1, ~'c');
  EXPECT_EQ(result.GetBytes(), expected_result);
}

/**
 * @brief Test for the operator+= method.
 */
TEST_F(BytesTest, AdditionAssignmentOperatorTest) {
  Bytes bytes1("hello");
  Bytes bytes2("world");
  bytes1 += bytes2;
  EXPECT_EQ(bytes1.GetBytes(), "helloworld");
}

/**
 * @brief Test for the operator^= method.
 */
TEST_F(BytesTest, XorAssignmentOperatorTest) {
  Bytes bytes1("abc");
  Bytes bytes2("def");
  bytes1 ^= bytes2;
  std::string expected_result = std::string(1, 'a' ^ 'd') + std::string(1, 'b' ^ 'e') + std::string(1, 'c' ^ 'f');
  EXPECT_EQ(bytes1.GetBytes(), expected_result);
}

/**
 * @brief Test for the operator|= method.
 */
TEST_F(BytesTest, OrAssignmentOperatorTest) {
  Bytes bytes1("abc");
  Bytes bytes2("def");
  bytes1 |= bytes2;
  std::string expected_result = std::string(1, 'a' | 'd') + std::string(1, 'b' | 'e') + std::string(1, 'c' | 'f');
  EXPECT_EQ(bytes1.GetBytes(), expected_result);
}

/**
 * @brief Test for the operator&= method.
 */
TEST_F(BytesTest, AndAssignmentOperatorTest) {
  Bytes bytes1("abc");
  Bytes bytes2("def");
  bytes1 &= bytes2;
  std::string expected_result = std::string(1, 'a' & 'd') + std::string(1, 'b' & 'e') + std::string(1, 'c' & 'f');
  EXPECT_EQ(bytes1.GetBytes(), expected_result);
}

/**
 * @brief Test for the operator<<= method.
 */
TEST_F(BytesTest, LeftShiftAssignmentOperatorTest) {
  Bytes bytes("abc");
  bytes <<= 1;
  std::string expected_result = std::string(1, 'a' << 1) + std::string(1, 'b' << 1) + std::string(1, 'c' << 1);
  EXPECT_EQ(bytes.GetBytes(), expected_result);
}

/**
 * @brief Test for the operator>>= method.
 */
TEST_F(BytesTest, RightShiftAssignmentOperatorTest) {
  Bytes bytes("abc");
  bytes >>= 1;
  std::string expected_result = std::string(1, 'a' >> 1) + std::string(1, 'b' >> 1) + std::string(1, 'c' >> 1);
  EXPECT_EQ(bytes.GetBytes(), expected_result);
}

/**
 * @brief Test for the operator== method.
 */
TEST_F(BytesTest, EqualityOperatorTest) {
  Bytes bytes1("test");
  Bytes bytes2("test");
  EXPECT_TRUE(bytes1 == bytes2);
}

/**
 * @brief Test for the operator!= method.
 */
TEST_F(BytesTest, InequalityOperatorTest) {
  Bytes bytes1("test1");
  Bytes bytes2("test2");
  EXPECT_TRUE(bytes1 != bytes2);
}

/**
 * @brief Test for the operator[] method.
 */
TEST_F(BytesTest, SubscriptOperatorTest) {
  Bytes bytes("test");
  EXPECT_EQ(bytes[0], 't');
}

/**
 * @brief Test for the toBigEndian() method.
 */
TEST_F(BytesTest, ToBigEndianTest) {
  Bytes bytes("test");
  EXPECT_EQ(bytes.toBigEndian(), "tset");
}

/**
 * @brief Test for the toLittleEndian() method.
 */
TEST_F(BytesTest, ToLittleEndianTest) {
  Bytes bytes("test");
  EXPECT_EQ(bytes.toLittleEndian(), "test");
}

/**
 * @brief Test for the FromBytesToBits() method.
 */
TEST_F(BytesTest, FromBytesToBitsTest) {
  Bytes bytes("A");
  EXPECT_EQ(bytes.FromBytesToBits(), "01000001");
}

/**
 * @brief Test for the FromBitsToBytes() method.
 */
TEST_F(BytesTest, FromBitsToBytesTest) {
  std::string bits = "01000001";
  EXPECT_EQ(Bytes::FromBitsToBytes(bits), "A");
}

/**
 * @brief Test for the FromBytesToHex() method.
 */
TEST_F(BytesTest, FromBytesToHexTest) {
  Bytes bytes("A");
  EXPECT_EQ(bytes.FromBytesToHex(), "41");
}

/**
 * @brief Test for the BitReverse() method.
 */
TEST_F(BytesTest, BitReverseTest) {
  Bytes bytes("12");
  Bytes result = bytes.BitReverse(2);
  EXPECT_EQ(result.FromBytesToHex(), "4c8c");
}