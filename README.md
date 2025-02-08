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

### Current Development Stage
- **Lexer**: Fully implemented 
- **Parser**: Initial implementation complete 
  * Basic function declaration parsing
  * Variable declaration support
  * Simple expression parsing
- **Abstract Syntax Tree (AST)**: Foundational structure defined
- **Interpreter/Compiler**: Planned 

### Parser Capabilities
- Recognize function declarations
- Parse variable assignments
- Handle basic expressions
- Provide error recovery mechanisms

### Upcoming Features
- Enhanced expression parsing
- Control flow statement support
- Type inference
- Semantic analysis

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

## Documentation

### Project Documentation
- [Lexer Output Explanation](/docs/lexer_output_explanation.md)
  * Detailed breakdown of lexer tokenization
  * Token type mapping
  * Insights into lexer implementation

### Additional Resources
- Comprehensive build instructions
- Project milestones and achievements
- Example scripts demonstrating language features

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

### Licensing Highlights
- Open-source and free to use
- Permissive licensing
- Allows commercial use
- Minimal restrictions on modification and distribution

## Contributing
We welcome contributions! Please see our contribution guidelines for more information.

## Building the Project

### Prerequisites
- CMake (version 3.20 or higher)
- C++ Compiler with C++20 support (GCC 10+, Clang 10+, MSVC 19.25+)
- Google Test (will be downloaded automatically if not found)

### Build Options

#### Quick Build
```bash
./configure.sh   # Configure the project
cd build         # Enter build directory
make             # Build the project
```

#### Comprehensive Build and Test
```bash
./build_and_test.sh
```
This script will:
- Check system dependencies
- Clean previous build artifacts
- Configure the project
- Build the project
- Run all tests

### Manual Build Steps
1. Create build directory
```bash
mkdir build
cd build
```

2. Configure with CMake
```bash
cmake ..
```

3. Build the project
```bash
make
```

4. Run tests
```bash
./novasyntax_test
```

### Build Configurations
- **Debug Build**: 
  ```bash
  cmake -DCMAKE_BUILD_TYPE=Debug ..
  ```
- **Release Build**: 
  ```bash
  cmake -DCMAKE_BUILD_TYPE=Release ..
  ```

### Troubleshooting
- Ensure all prerequisites are installed
- Check that you have a compiler supporting C++20
- If Google Test is not found, it will be automatically downloaded
- For any build issues, please file an issue on GitHub

## Test Results

### Lexer Test Outcomes

┌─────────────────────────────────────────────────────────────────┐
│ Test Suite: LexerTest                                           │
│ Total Tests: 4                                                 │
│ Passed: 4                                                      │
│ Failed: 0                                                      │
│                                                                │
│ Successful Tests:                                              │
│ - BasicTokenization                                            │
│ - StringTokenization                                           │
│ - NumberTokenization                                           │
│ - ComplexTokenization                                          │
└─────────────────────────────────────────────────────────────────┘

**Detailed Test Breakdown:**

1. **BasicTokenization Test**
   - Input: `func add(x, y) { return x + y }`
   - **Passed**: Correctly tokenized function definition

2. **StringTokenization Test**
   - Input: `let message = "Hello, NovaSyntax!"`
   - **Passed**: Correctly tokenized string literal

3. **NumberTokenization Test**
   - Input: `let x = 42.5`
   - **Passed**: Correctly tokenized numeric literal

4. **ComplexTokenization Test**
   - Input: `let x = 42.5e-2 + 0xAF + 0b1010`
   - **Passed**: Correctly tokenized complex number formats
     * Scientific notation (`42.5e-2`)
     * Hexadecimal literal (`0xAF`)
     * Binary literal (`0b1010`)

**Recent Improvements:**
- Enhanced lexer to support advanced number representations
- Added robust parsing for scientific notation
- Implemented tokenization of hexadecimal and binary literals
- Expanded test coverage for complex token scenarios

### Parser Test Outcomes

┌─────────────────────────────────────────────────────────────────┐
│ Test Suite: ParserTest                                          │
│ Total Tests: 4                                                 │
│ Passed: 4                                                      │
│ Failed: 0                                                      │
│                                                                │
│ Successful Tests:                                              │
│ - BasicFunctionDeclaration                                     │
│ - VariableDeclaration                                          │
│ - SimpleExpression                                             │
│ - ErrorRecovery                                                │
└─────────────────────────────────────────────────────────────────┘

**Detailed Test Breakdown:**

1. **BasicFunctionDeclaration Test**
   - Input: `func add(x, y) { x }`
   - **Passed**: Correctly parsed function declaration with parameters

2. **VariableDeclaration Test**
   - Input: `let x = 42`
   - **Passed**: Correctly parsed variable declaration with numeric literal

3. **SimpleExpression Test**
   - Input: `42`
   - **Passed**: Correctly parsed simple numeric expression

4. **ErrorRecovery Test**
   - Input: Malformed function declaration
   - **Passed**: Demonstrated error handling and recovery mechanisms