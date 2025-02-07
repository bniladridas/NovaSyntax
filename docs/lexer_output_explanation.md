# NovaSyntax Lexer Output Explanation

## Token Types Mapping

| Type Number | Token Type | Description |
|------------|------------|-------------|
| 0 | IDENTIFIER | Variable or function names |
| 1 | NUMBER | Numeric literals (decimal, scientific, hex, binary) |
| 2 | STRING | String literals |
| 3 | FUNCTION | Function declaration keyword |
| 4 | LET | Variable declaration keyword |
| 7 | RETURN | Return statement keyword |
| 8 | PLUS | Addition operator |
| 12 | ASSIGN | Assignment operator `=` |
| 13 | LPAREN | Left parenthesis `(` |
| 14 | RPAREN | Right parenthesis `)` |
| 15 | LBRACE | Left curly brace `{` |
| 17 | RBRACE | Right curly brace `}` |
| 18 | COMMA | Comma `,` |
| 19 | EOF | End of file marker |

## Sample Lexer Output

### Input Script
```novasyntax
func calculate(x, y) {
    let result = x + y
    let message = "Calculation complete"
    return result
}
```

### Tokenization Breakdown

```
Type: 3, Literal: func, Line: 2, Column: 10
  - Function declaration keyword

Type: 0, Literal: calculate, Line: 2, Column: 15
  - Function name (identifier)

Type: 13, Literal: (, Line: 2, Column: 24
  - Left parenthesis

Type: 0, Literal: x, Line: 2, Column: 25
  - First parameter (identifier)

Type: 18, Literal: ,, Line: 2, Column: 26
  - Comma separating parameters

Type: 0, Literal: y, Line: 2, Column: 28
  - Second parameter (identifier)

Type: 14, Literal: ), Line: 2, Column: 29
  - Right parenthesis

Type: 15, Literal: {, Line: 2, Column: 31
  - Left curly brace (start of function body)

... (other tokens follow similar pattern)
```

## Implementation Insights

### Lexer Tokenization Process
1. Read input character by character
2. Identify token type based on current character
3. Consume characters to form complete tokens
4. Track line and column information
5. Handle different token types:
   - Keywords
   - Identifiers
   - Numeric literals
   - Operators
   - Punctuation

### Future Enhancements
- Improve error handling for invalid tokens
- Add more sophisticated token recognition
- Support more complex language constructs
