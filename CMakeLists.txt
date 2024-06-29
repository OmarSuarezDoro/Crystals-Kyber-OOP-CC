# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Grado en Ingeniería Informática
# Build process:
#   1. cd <project_folder>
#   2. mkdir build
#   3. cd build
#   4. cmake ..
#   5. make

# Set the minimum Version of CMAKE required
cmake_minimum_required(VERSION 3.1)

# Set the Project configs
project(
  CrystalKyber
  VERSION 1.0
  DESCRIPTION "CrystalKyber Implementation in C++"
  LANGUAGES CXX
)

# Specify the C++ standard to use
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Locate GTest Directories
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})

# Set the output binaries in this folders:
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# Debug and release flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -pedantic -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Set the location of *.h files
include_directories(${PROJECT_SOURCE_DIR}/src)

# # Adds an executable target called "runTests" to be built from the source files listed in the command invocation.
# add_executable(
#   runTests
#   test/gtest_main.cc
#   test/test_04-mov.cc
#   src/04-mov.h
#   src/04-mov.cc
# )

# Adds an executable target called "04-mov_main" to be built from the source files listed in the command invocation.
add_executable(
  client_main
  src/client.cc
)

# target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

# # Add expected compiler features to a target.
# target_compile_features(runTests PRIVATE cxx_std_17)

# Add compile options to a target.
# target_compile_options(runTests PRIVATE -Wall -Wextra -Wpedantic)
target_compile_options(client_main PRIVATE -Wall -Wextra -Wpedantic)