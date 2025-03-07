#pragma once

#include <string>
#include <vector>
#include <variant>

namespace novasyntax {

enum class TokenType {
    // Basic token types
    IDENTIFIER,
    NUMBER,
    STRING,
    
    // Keywords
    FUNCTION,
    LET,
    IF,
    ELSE,
    RETURN,
    
    // Operators
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    ASSIGN,  // New token type for '='
    
    // Delimiters
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACKET, // New token type
    RBRACE,
    COMMA,  // New token type for ','
    
    // Special
    EOF_  // Rename to EOF_
};

struct Token {
    TokenType type;
    std::string literal;
    int line;
    int column;
};

class Lexer {
public:
    Lexer(const std::string& source);
    std::vector<Token> tokenize();

private:
    std::string source;
    size_t current;
    size_t start;
    int line;
    int column;

    char advance();
    char peek();
    bool isAtEnd();
    void skipWhitespace();
    Token createToken(TokenType type);
    Token identifierToken();
    Token numberToken();
    Token stringToken();
};

} // namespace novasyntax
