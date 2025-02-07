#include "lexer.hpp"
#include <iostream>
#include <stdexcept>
#include <cctype>

namespace novasyntax {

Lexer::Lexer(const std::string& source) 
    : source(source), current(0), line(1), column(1) {}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    std::cout << "Source: '" << source << "'" << std::endl;
    std::cout << "Source Length: " << source.length() << std::endl;

    while (!isAtEnd()) {
        skipWhitespace();
        start = current;
        if (isAtEnd()) break;

        char ch = peek();
        std::cout << "Current Position: " << current 
                  << ", Current Char: '" << ch 
                  << "', Remaining Source: '" 
                  << source.substr(current) << "'" << std::endl;

        switch (ch) {
            case '(': 
                tokens.push_back(createToken(TokenType::LPAREN)); 
                advance(); 
                // Explicitly capture the first identifier after LPAREN
                skipWhitespace();
                if (!isAtEnd() && (std::isalpha(peek()) || peek() == '_')) {
                    size_t start_id = current;
                    while (!isAtEnd() && (std::isalnum(peek()) || peek() == '_')) {
                        advance();
                    }
                    std::string literal = source.substr(start_id, current - start_id);
                    tokens.push_back({TokenType::IDENTIFIER, literal, line, static_cast<int>(column - literal.length())});
                }
                break;
            case ')': tokens.push_back(createToken(TokenType::RPAREN)); advance(); break;
            case '{': tokens.push_back(createToken(TokenType::LBRACE)); advance(); break;
            case '}': tokens.push_back(createToken(TokenType::RBRACE)); advance(); break;
            case '+': tokens.push_back(createToken(TokenType::PLUS)); advance(); break;
            case '-': tokens.push_back(createToken(TokenType::MINUS)); advance(); break;
            case '*': tokens.push_back(createToken(TokenType::MULTIPLY)); advance(); break;
            case '/': tokens.push_back(createToken(TokenType::DIVIDE)); advance(); break;
            case '=': tokens.push_back(createToken(TokenType::ASSIGN)); advance(); break;
            case ',': 
                tokens.push_back(createToken(TokenType::COMMA)); 
                advance(); 
                // Capture identifier after COMMA
                skipWhitespace();
                if (!isAtEnd() && (std::isalpha(peek()) || peek() == '_')) {
                    size_t start_id = current;
                    while (!isAtEnd() && (std::isalnum(peek()) || peek() == '_')) {
                        advance();
                    }
                    std::string literal = source.substr(start_id, current - start_id);
                    tokens.push_back({TokenType::IDENTIFIER, literal, line, static_cast<int>(column - literal.length())});
                }
                break;

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
                    // Skip whitespace and unknown characters
                    skipWhitespace();
                    if (!isAtEnd()) {
                        advance(); // Ensure progress
                    }
                }
        }
    }
    
    // Always add EOF token at the end
    tokens.push_back({TokenType::EOF_, "<EOF>", line, column});
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
    Token token{type, std::string(1, advance()), line, column - 1};
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
    while (!isAtEnd() && std::isdigit(peek())) {
        advance();
    }

    // Handle decimal point
    if (peek() == '.' && !isAtEnd()) {
        advance();
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