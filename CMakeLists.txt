# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Dependencies:
#   - GTest -> sudo apt install libgtest-dev
# Build process:
#   1. cd <project_folder>
#   2. mkdir build
#   3. cd build
#   4. cmake ..
#   5. make

# Set the minimum Version of CMAKE required
cmake_minimum_required(VERSION 3.14)

# Set the Project configs
project(
  Crystals-Kyber
  VERSION 1.0
  DESCRIPTION "Crystals-Kyber Implementation in C++"
  LANGUAGES CXX
)

# Debug and release flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


# Specify the C++ standard to use
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


# Set the location of *.h files
include_directories(${PROJECT_SOURCE_DIR}/src)

# Adds an executable target called "runTests" to be built from the source files listed in the command invocation.
add_executable(
  runTests
  test/gtest_main.cc
  test/Bytes.cc
  test/Matrix.cc
  test/Polynomial.cc
  test/Keccak.cc
  test/NTT.cc
  test/PWMUnit.cc
  test/SamplingUnit.cc
  test/EncDecUnit.cc
  test/CompressorUnit.cc
  ./src/DataStructures/Bytes.cc
  ./src/Components/Keccak.cc
  ./src/Components/NTT.cc
  ./src/Components/NTT.h
  ./src/Components/PWMUnit.cc
  ./src/Components/PWMUnit.h
  ./src/Components/SamplingUnit.cc
  ./src/Components/SamplingUnit.h
  ./src/Components/EncDecUnit.cc
  ./src/Components/EncDecUnit.h
  ./src/Components/CompressorUnit.cc
  ./src/Components/CompressorUnit.h
  )

# Adds an executable target called "client_main" to be built from the source files listed in the command invocation.
add_executable(
  client_main
  ./src/client.cc
  ./src/DataStructures/Polynomial.h
  ./src/DataStructures/Matrix.h
  ./src/DataStructures/Bytes.cc
  ./src/DataStructures/Bytes.h
  ./src/Components/Keccak.cc
  ./src/Components/Keccak.h
  ./src/Components/NTT.cc
  ./src/Components/NTT.h
  ./src/Components/SamplingUnit.cc
  ./src/Components/SamplingUnit.h
  ./src/Components/PWMUnit.cc
  ./src/Components/PWMUnit.h
  ./src/Components/EncDecUnit.cc
  ./src/Components/EncDecUnit.h
  ./src/Components/CompressorUnit.cc
  ./src/Components/CompressorUnit.h
  )


# Add Crypto++ library
link_directories(/usr/include/cryptopp/lib)
target_link_libraries(client_main cryptopp)
target_link_libraries(runTests cryptopp)

# Add expected compiler features to a target.
target_compile_features(runTests PRIVATE cxx_std_17)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

# Add compile options to a target.
target_compile_options(runTests PRIVATE)
target_compile_options(client_main PRIVATE)