#include "../../include/parser/parser.h"
#include <stdexcept>
#include <sstream>
#include <iostream>

namespace novasyntax {

Parser::Parser(const std::vector<Token>& tokens) : tokens_(tokens) {
    std::cout << "Parser initialized with " << tokens.size() << " tokens\n";
    if (tokens_.empty()) {
        throw std::runtime_error("Cannot parse empty token stream");
    }
}

std::unique_ptr<ASTNode> Parser::parse() {
    try {
        if (is_at_end()) {
            std::cerr << "Reached end of token stream\n";
            return nullptr;
        }

        std::cout << "Parsing first token: " 
                  << "Type=" << static_cast<int>(peek().type) 
                  << ", Literal='" << peek().literal << "'\n";

        if (peek().type == TokenType::FUNCTION) {
            std::cout << "Parsing function declaration\n";
            return parseFunctionDeclaration();
        }
        if (peek().type == TokenType::LET) {
            std::cout << "Parsing variable declaration\n";
            return parseVariableDeclaration();
        }
        std::cout << "Parsing expression\n";
        return parseExpression();
    } catch (const std::runtime_error& e) {
        std::cerr << "Parsing error: " << e.what() << std::endl;
        return nullptr;
    } catch (...) {
        std::cerr << "Unknown parsing error occurred\n";
        return nullptr;
    }
}

std::unique_ptr<FunctionDeclaration> Parser::parseFunctionDeclaration() {
    auto func_decl = std::make_unique<FunctionDeclaration>();

    try {
        // Consume 'func' keyword
        consume(TokenType::FUNCTION, "Expect 'func' at the start of function declaration");

        // Parse function name
        func_decl->name = consume(TokenType::IDENTIFIER, "Expect function name").literal;
        std::cout << "Function name: " << func_decl->name << std::endl;

        // Consume opening parenthesis
        consume(TokenType::LPAREN, "Expect '(' after function name");

        // Parse parameters
        while (!is_at_end() && peek().type != TokenType::RPAREN) {
            func_decl->parameters.push_back(
                consume(TokenType::IDENTIFIER, "Expect parameter name").literal
            );

            if (peek().type == TokenType::COMMA) {
                advance(); // Consume comma
            }

            // Prevent infinite loop
            if (is_at_end()) {
                throw std::runtime_error("Unexpected end of token stream in function declaration");
            }
        }

        // Consume closing parenthesis
        consume(TokenType::RPAREN, "Expect ')' after parameters");

        // Consume opening brace
        consume(TokenType::LBRACE, "Expect '{' before function body");

        // Parse function body (simplified for now)
        // In a full implementation, this would parse statements
        func_decl->body = parseExpression();

        // Consume closing brace
        consume(TokenType::RBRACE, "Expect '}' after function body");

        return func_decl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error parsing function declaration: " << e.what() << std::endl;
        return nullptr;
    }
}

std::unique_ptr<VariableDeclaration> Parser::parseVariableDeclaration() {
    try {
        auto var_decl = std::make_unique<VariableDeclaration>();

        // Consume 'let' keyword
        consume(TokenType::LET, "Expect 'let' at the start of variable declaration");

        // Parse variable name
        var_decl->name = consume(TokenType::IDENTIFIER, "Expect variable name").literal;

        // Consume assignment
        consume(TokenType::ASSIGN, "Expect '=' after variable name");

        // Parse initializer expression
        var_decl->initializer = parseExpression();

        return var_decl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error parsing variable declaration: " << e.what() << std::endl;
        return nullptr;
    }
}

std::unique_ptr<Expression> Parser::parseExpression() {
    try {
        auto expr = std::make_unique<Expression>();

        // Simplified expression parsing
        if (peek().type == TokenType::NUMBER) {
            expr->type = Expression::Type::LITERAL;
            expr->value = advance().literal;
        } else if (peek().type == TokenType::IDENTIFIER) {
            expr->type = Expression::Type::LITERAL;
            expr->value = advance().literal;
        } else if (peek().type == TokenType::STRING) {
            expr->type = Expression::Type::STRING_LITERAL;
            expr->value = advance().literal;
        } else {
            std::cerr << "Unexpected token type: " 
                      << static_cast<int>(peek().type) << std::endl;
            throw std::runtime_error("Unexpected token in expression");
        }

        return expr;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error parsing expression: " << e.what() << std::endl;
        return nullptr;
    }
}

Token Parser::consume(TokenType type, const std::string& error_message) {
    try {
        std::cout << "Consuming token. Expected: " << static_cast<int>(type) 
                  << ", Current: " << static_cast<int>(peek().type) << std::endl;
        
        if (is_at_end()) {
            throw std::runtime_error("Unexpected end of token stream");
        }

        if (peek().type == type) {
            return advance();
        }
        
        std::stringstream ss;
        ss << "Token mismatch. Expected: " << static_cast<int>(type) 
           << ", Got: " << static_cast<int>(peek().type);
        throw std::runtime_error(ss.str());
    } catch (const std::runtime_error& e) {
        std::cerr << "Error consuming token: " << e.what() << std::endl;
        throw;
    }
}

bool Parser::is_at_end() {
    // Ensure we're within bounds and check for EOF
    return current_token_ >= tokens_.size() || 
           (current_token_ < tokens_.size() && 
            (peek().type == TokenType::EOF_ || 
             current_token_ == tokens_.size() - 1));
}

Token Parser::peek() {
    // Defensive peek to prevent out-of-bounds access
    if (current_token_ >= tokens_.size()) {
        // If we're past the end, return the last token
        return tokens_.back();
    }
    return tokens_[current_token_];
}

Token Parser::previous() {
    if (current_token_ == 0) {
        throw std::runtime_error("Cannot get previous token at start of stream");
    }
    return tokens_[current_token_ - 1];
}

Token Parser::advance() {
    if (!is_at_end()) current_token_++;
    return previous();
}

void Parser::synchronize() {
    advance();

    while (!is_at_end()) {
        if (previous().type == TokenType::RBRACE) return;

        switch (peek().type) {
            case TokenType::FUNCTION:
            case TokenType::LET:
            case TokenType::RETURN:
                return;
            default:
                advance();
        }
    }
}

// AST Node toString methods
std::string FunctionDeclaration::toString() const {
    std::stringstream ss;
    ss << "Function: " << name << "(";
    for (const auto& param : parameters) {
        ss << param << " ";
    }
    ss << ")";
    return ss.str();
}

std::string VariableDeclaration::toString() const {
    return "Variable: " + name;
}

std::string Expression::toString() const {
    if (type == Type::STRING_LITERAL) {
        return "String Literal: " + value;
    } else {
        return "Expression: " + value;
    }
}

} // namespace novasyntax
