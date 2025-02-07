#!/bin/bash

# Check if cmake is installed
if ! command -v cmake &> /dev/null
then
    echo "cmake could not be found, please install cmake."
    exit 1
fi

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
  mkdir build
fi

# Navigate to build directory
cd build

# Run cmake configuration
cmake ..

# Exit with the status of the last command
exit $?
