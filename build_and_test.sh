#!/bin/bash

# Exit on any error
set -e

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Run CMake to generate build files
cmake ..

# Build the project
cmake --build .

# Check if main executable exists
if [ -f novasyntax ]; then
    echo "Running main executable:"
    ./novasyntax
else
    echo "Main executable not found!"
fi

# Check if test executable exists
if [ -f novasyntax_test ]; then
    echo "Running tests:"
    ./novasyntax_test
else
    echo "Test executable not found!"
fi
