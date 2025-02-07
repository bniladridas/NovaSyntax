#include "lexer.hpp"
#include <iostream>
#include <stdexcept>
#include <cctype>

namespace novasyntax {

Lexer::Lexer(const std::string& source) 
    : source(source), current(0), line(1), column(1) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    current = 0;
    line = 1;
    column = 1;

    while (!isAtEnd()) {
        skipWhitespace();
        start = current;
        if (isAtEnd()) break;

        char ch = peek();

        switch (ch) {
            case '(': {
                tokens.push_back({TokenType::LPAREN, "(", line, column});
                advance();
                skipWhitespace();
                
                // Explicitly capture identifier after LPAREN
                if (!isAtEnd() && (std::isalpha(peek()) || peek() == '_')) {
                    size_t start_id = current;
                    while (!isAtEnd() && (std::isalnum(peek()) || peek() == '_')) {
                        advance();
                    }
                    std::string literal = source.substr(start_id, current - start_id);
                    tokens.push_back({TokenType::IDENTIFIER, literal, line, static_cast<int>(column - literal.length())});
                }
                break;
            }
            case ')': tokens.push_back({TokenType::RPAREN, ")", line, column}); advance(); break;
            case '{': tokens.push_back({TokenType::LBRACE, "{", line, column}); advance(); break;
            case '}': tokens.push_back({TokenType::RBRACE, "}", line, column}); advance(); break;
            case '+': tokens.push_back({TokenType::PLUS, "+", line, column}); advance(); break;
            case '-': tokens.push_back({TokenType::MINUS, "-", line, column}); advance(); break;
            case '*': tokens.push_back({TokenType::MULTIPLY, "*", line, column}); advance(); break;
            case '/': tokens.push_back({TokenType::DIVIDE, "/", line, column}); advance(); break;
            case '=': tokens.push_back({TokenType::ASSIGN, "=", line, column}); advance(); break;
            case ',': {
                tokens.push_back({TokenType::COMMA, ",", line, column});
                advance();
                skipWhitespace();
                
                // Explicitly capture identifier after COMMA
                if (!isAtEnd() && (std::isalpha(peek()) || peek() == '_')) {
                    size_t start_id = current;
                    while (!isAtEnd() && (std::isalnum(peek()) || peek() == '_')) {
                        advance();
                    }
                    std::string literal = source.substr(start_id, current - start_id);
                    tokens.push_back({TokenType::IDENTIFIER, literal, line, static_cast<int>(column - literal.length())});
                }
                break;
            }

            default:
                if (std::isalpha(ch) || ch == '_') {
                    tokens.push_back(identifierToken());
                }
                else if (std::isdigit(ch)) {
                    tokens.push_back(numberToken());
                }
                else if (ch == '"') {
                    tokens.push_back(stringToken());
                }
                else {
                    skipWhitespace();
                    if (!isAtEnd()) {
                        advance(); // Ensure progress
                    }
                }
        }
    }
    
    // Always add EOF token at the end
    tokens.push_back({TokenType::EOF_, "<EOF>", line, static_cast<int>(column + 1)});
    
    return tokens;
}

char Lexer::advance() {
    column++;
    return source[current++];
}

char Lexer::peek() {
    if (isAtEnd()) return '\0';
    return source[current];
}

bool Lexer::isAtEnd() {
    return current >= source.length();
}

void Lexer::skipWhitespace() {
    while (!isAtEnd() && std::isspace(peek())) {
        if (peek() == '\n') {
            line++;
            column = 1;
        }
        advance();
    }
}

Token Lexer::createToken(TokenType type) {
    Token token{type, std::string(1, advance()), line, static_cast<int>(column - 1)};
    return token;
}

Token Lexer::identifierToken() {
    size_t start = current;
    while (!isAtEnd() && (std::isalnum(peek()) || peek() == '_')) {
        advance();
    }

    std::string literal = source.substr(start, current - start);
    TokenType type = TokenType::IDENTIFIER;

    // Check for keywords
    if (literal == "func") {
        type = TokenType::FUNCTION;
    } else if (literal == "let") {
        type = TokenType::LET;
    } else if (literal == "if") {
        type = TokenType::IF;
    } else if (literal == "else") {
        type = TokenType::ELSE;
    } else if (literal == "return") {
        type = TokenType::RETURN;
    }

    return {type, literal, line, static_cast<int>(column - literal.length())};
}

Token Lexer::numberToken() {
    size_t start = current;
    bool hasExponent = false;

    // Check for hex or binary literals
    if (peek() == '0') {
        advance(); // consume '0'
        if (peek() == 'x' || peek() == 'X') {
            advance(); // consume 'x'
            // Validate hex digits
            if (!std::isxdigit(peek())) {
                throw std::runtime_error("Invalid hexadecimal literal");
            }
            while (!isAtEnd() && std::isxdigit(peek())) {
                advance();
            }
            std::string literal = source.substr(start, current - start);
            return {TokenType::NUMBER, literal, line, static_cast<int>(column - literal.length())};
        } else if (peek() == 'b' || peek() == 'B') {
            advance(); // consume 'b'
            // Validate binary digits
            if (peek() != '0' && peek() != '1') {
                throw std::runtime_error("Invalid binary literal");
            }
            while (!isAtEnd() && (peek() == '0' || peek() == '1')) {
                advance();
            }
            std::string literal = source.substr(start, current - start);
            return {TokenType::NUMBER, literal, line, static_cast<int>(column - literal.length())};
        } else {
            // Revert back for decimal processing
            current = start;
        }
    }

    // Process digits for decimal numbers
    // Integer part
    while (!isAtEnd() && std::isdigit(peek())) {
        advance();
    }

    // Optional decimal part
    if (peek() == '.' && !hasExponent) {
        advance(); // decimal point
        while (!isAtEnd() && std::isdigit(peek())) {
            advance();
        }
    }

    // Optional exponent
    if ((peek() == 'e' || peek() == 'E') && !hasExponent) {
        advance(); // exponent marker
        hasExponent = true;

        // Optional sign for exponent
        if (peek() == '+' || peek() == '-') {
            advance();
        }

        // Ensure at least one digit after exponent
        if (!std::isdigit(peek())) {
            throw std::runtime_error("Invalid exponent in number literal");
        }

        // Consume exponent digits
        while (!isAtEnd() && std::isdigit(peek())) {
            advance();
        }
    }

    std::string literal = source.substr(start, current - start);
    return {TokenType::NUMBER, literal, line, static_cast<int>(column - literal.length())};
}

Token Lexer::stringToken() {
    advance(); // consume opening quote
    size_t start = current;

    while (!isAtEnd() && peek() != '"') {
        if (peek() == '\n') {
            line++;
            column = 1;
        }
        advance();
    }

    if (isAtEnd()) {
        throw std::runtime_error("Unterminated string");
    }

    std::string literal = source.substr(start, current - start);
    advance(); // consume closing quote

    return {TokenType::STRING, literal, line, static_cast<int>(column - literal.length() - 2)};
}

} // namespace novasyntax