#!/bin/bash

# Strict mode
set -euo pipefail

# Color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Logging function
log() {
    echo -e "${YELLOW}[BUILD LOG]${NC} $1"
}

# Error handling function
error() {
    echo -e "${RED}[ERROR]${NC} $1" >&2
    exit 1
}

# Cleanup function
cleanup() {
    if [ -d "build" ]; then
        log "Cleaning up previous build directory"
        rm -rf build
    fi
}

# Check for required dependencies
check_dependencies() {
    log "Checking dependencies..."
    command -v cmake >/dev/null 2>&1 || error "CMake is not installed"
    command -v make >/dev/null 2>&1 || error "Make is not installed"
    command -v g++ >/dev/null 2>&1 || error "G++ compiler is not installed"
}

# Main build process
build() {
    log "Creating build directory"
    mkdir -p build
    cd build

    log "Configuring project with CMake"
    cmake .. || error "CMake configuration failed"

    log "Building project"
    make || error "Build failed"
}

# Run tests
run_tests() {
    log "Running tests"
    if [ -f novasyntax_test ]; then
        ./novasyntax_test || error "Tests failed"
        echo -e "${GREEN}All tests passed successfully!${NC}"
    else
        error "Test executable not found"
    fi
}

# Main script execution
main() {
    log "Starting NovaSyntax build and test process"
    
    cleanup
    check_dependencies
    build
    run_tests

    log "Build and test process completed successfully"
}

# Run the main function
main
