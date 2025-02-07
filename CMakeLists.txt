cmake_minimum_required(VERSION 3.20)
project(NovaSyntax VERSION 0.1.0 LANGUAGES CXX)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(include)

# Find Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Source files
set(SOURCES
    src/lexer/lexer.cpp
)

# Create library
add_library(novasyntax_lib ${SOURCES})

# Create executable
add_executable(novasyntax src/main.cpp)
target_link_libraries(novasyntax novasyntax_lib)

# Enable testing
enable_testing()

# Add test executable
add_executable(novasyntax_test tests/lexer_test.cpp)
target_link_libraries(novasyntax_test 
    novasyntax_lib
    ${GTEST_LIBRARIES}
    pthread
)

# Discover tests
include(GoogleTest)
gtest_discover_tests(novasyntax_test)
