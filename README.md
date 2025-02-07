# NovaSyntax

## Project Overview

NovaSyntax is a custom programming language implementation project, currently in its early stages of development. The key aspects of the project are:

### Language Design
- A new programming language being developed from scratch
- Appears to have syntax similar to modern scripting languages
- Supports basic language constructs like:
  - Function declarations (`func`)
  - Variable declarations (`let`)
  - Return statements
  - Basic arithmetic operations

### Current Focus
- Lexical Analysis (Tokenization)
- Building a robust lexer that can correctly parse and tokenize source code
- Implementing a token system that captures different language elements

### Technical Implementation
- Written in C++
- Using Google Test framework for unit testing
- Modular design with separate components for lexing

### Current Development Stage
- Working on fundamental lexer functionality
- Debugging token generation
- Ensuring correct identification of language tokens

### Example Syntax
```novasyntax
func add(x, y) { return x + y }
let message = "Hello, NovaSyntax!"
let x = 42.5
```

The project is currently focused on building the lexical analysis component, which is the first step in creating a programming language compiler or interpreter. The lexer breaks down the source code into a sequence of tokens that can be further processed by subsequent stages like parsing and compilation.

## Project Structure
- `src/lexer/`: Lexer implementation
- `include/`: Header files
- `tests/`: Unit tests for lexer and other components

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