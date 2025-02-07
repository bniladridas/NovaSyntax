> **NovaSyntax** is intended to be a full-fledged programming language, similar to C, Python, or other general-purpose programming languages. However, it's currently in a very early stage of development.

### Similarities to C and Python
- Supports function declarations
- Has variable declarations
- Supports basic arithmetic operations
- Uses curly braces `{}` for code blocks
- Designed to be a compiled or interpreted language

### Relationship to C++
#### Similarities to C++
- Uses curly braces `{}` to define code blocks
- Supports function declarations
- Uses static typing (implied by the current implementation)
- Uses `return` statement
- Appears to have a compiled language approach
- Being implemented in C++

#### Differences from C++
- Simpler syntax (more like a scripting language)
- Uses `func` instead of C++'s function declaration style
- Uses `let` for variable declaration (more like JavaScript/Rust)
- Likely to have a simpler type system
- Currently much less feature-complete
- No explicit type annotations shown in current examples
- No object-oriented programming features yet
- No templates or generic programming
- No explicit memory management keywords

### Unique Characteristics
- Has its own custom syntax (e.g., `func` instead of `def` or no return type)
- Currently only implementing the lexer (first stage of language implementation)
- Will eventually need:
  1. Parser
  2. Compiler or Interpreter
  3. Standard Library
  4. Runtime Environment

### Current Stage
Right now, NovaSyntax is more of a "language skeleton" - we're building the foundational components that will eventually allow it to be a fully functional programming language like C or Python.

### Language Development Process
The project is essentially creating a new programming language from scratch, which involves:
- Defining the language syntax
- Creating a lexer to break down code into tokens
- Developing a parser to understand code structure
- Implementing compilation or interpretation mechanisms

### Example Syntax
```novasyntax
func add(x, y) { return x + y }
let message = "Hello, NovaSyntax!"
let x = 42.5
```

## Project Structure
- `src/lexer/`: Lexer implementation
- `include/`: Header files
- `tests/`: Unit tests for lexer and other components

## Building the Project

### Prerequisites
- CMake
- C++ Compiler (e.g., Clang, GCC)

### Configuration Script
A `configure.sh` script is provided to simplify the CMake configuration process:

```bash
./configure.sh
```

This script does the following:
- Checks if CMake is installed
- Creates a `build` directory if it doesn't exist
- Runs CMake configuration

### Manual Configuration
If you prefer manual configuration:
```bash
mkdir build
cd build
cmake ..
```

### Building the Project
After configuration:
```bash
cd build
make
```

### Running Tests
```bash
./novasyntax_test
```

## Test Results

### Lexer Test Outcomes

┌─────────────────────────────────────────────────────────────────┐
│ Test Suite: LexerTest                                           │
│ Total Tests: 3                                                 │
│ Passed: 2                                                      │
│ Failed: 1                                                      │
│                                                                │
│ Failed Test: BasicTokenization                                 │
│ Failure Reason: Token count mismatch                           │
│   - Expected: 14 tokens                                        │
│   - Actual:   13 tokens                                        │
│                                                                │
│ Successful Tests:                                              │
│ - StringTokenization                                           │
│ - NumberTokenization                                           │
└─────────────────────────────────────────────────────────────────┘

**Detailed Test Breakdown:**

1. **BasicTokenization Test**
   - Input: `func add(x, y) { return x + y }`
   - **Failed**: Expected 14 tokens, but only 13 tokens were generated
   - Missing token is likely the first identifier `x`

2. **StringTokenization Test**
   - Input: `let message = "Hello, NovaSyntax!"`
   - **Passed**: Correctly tokenized string literal

3. **NumberTokenization Test**
   - Input: `let x = 42.5`
   - **Passed**: Correctly tokenized numeric literal

**Next Steps:**
- Investigate why the first `x` identifier is not being captured in the BasicTokenization test
- Modify the lexer to ensure all identifiers are correctly tokenized