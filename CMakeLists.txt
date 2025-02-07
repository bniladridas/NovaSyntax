cmake_minimum_required(VERSION 3.20)
project(NovaSyntax 
    VERSION 0.1.0 
    DESCRIPTION "A custom programming language implementation"
    LANGUAGES CXX
)

# Ensure out-of-source build
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a separate build directory.")
endif()

# Set C++20 standard with fallback
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add compiler warnings for better code quality
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build" FORCE)
endif()

# Add include directories with error checking
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/include")
    message(FATAL_ERROR "Include directory not found!")
endif()
include_directories(include)

# Find Google Test with graceful fallback
find_package(GTest QUIET)
if(NOT GTEST_FOUND)
    message(WARNING "Google Test not found. Attempting to download...")
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

# Source files with error checking
set(SOURCES
    src/lexer/lexer.cpp
)
foreach(SOURCE ${SOURCES})
    if(NOT EXISTS "${CMAKE_SOURCE_DIR}/${SOURCE}")
        message(FATAL_ERROR "Source file not found: ${SOURCE}")
    endif()
endforeach()

# Create library
add_library(novasyntax_lib STATIC ${SOURCES})
set_target_properties(novasyntax_lib PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

# Create executable
add_executable(novasyntax src/main.cpp)
target_link_libraries(novasyntax PRIVATE novasyntax_lib)

# Enable testing
enable_testing()

# Add test executable
add_executable(novasyntax_test tests/lexer_test.cpp)
target_link_libraries(novasyntax_test 
    PRIVATE
    novasyntax_lib
    GTest::gtest_main
    pthread
)

# Discover tests
include(GoogleTest)
gtest_discover_tests(novasyntax_test)

# Optional: Add install target
install(
    TARGETS novasyntax novasyntax_lib
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static
)

# Print build configuration summary
message(STATUS "Build Configuration:")
message(STATUS "  Project: ${PROJECT_NAME}")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
