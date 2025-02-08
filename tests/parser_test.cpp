#include <gtest/gtest.h>
#include "../include/lexer.hpp"
#include "../include/parser/parser.h"
#include <memory>
#include <iostream>

// Utility function to create tokens
std::vector<novasyntax::Token> createTokens(std::initializer_list<std::pair<novasyntax::TokenType, std::string>> tokenList) {
    std::vector<novasyntax::Token> tokens;
    for (const auto& [type, literal] : tokenList) {
        tokens.push_back({type, literal, 1, 1});
    }
    tokens.push_back({novasyntax::TokenType::EOF_, "", 1, 1});
    
    // Debug print tokens
    std::cout << "Created " << tokens.size() << " tokens:\n";
    for (const auto& token : tokens) {
        std::cout << "Token: Type=" << static_cast<int>(token.type) 
                  << ", Literal='" << token.literal << "'\n";
    }
    
    return tokens;
}

TEST(ParserTest, BasicFunctionDeclaration) {
    auto tokens = createTokens({
        {novasyntax::TokenType::FUNCTION, "func"},
        {novasyntax::TokenType::IDENTIFIER, "add"},
        {novasyntax::TokenType::LPAREN, "("},
        {novasyntax::TokenType::IDENTIFIER, "x"},
        {novasyntax::TokenType::COMMA, ","},
        {novasyntax::TokenType::IDENTIFIER, "y"},
        {novasyntax::TokenType::RPAREN, ")"},
        {novasyntax::TokenType::LBRACE, "{"},
        {novasyntax::TokenType::IDENTIFIER, "x"}, // Simplified body
        {novasyntax::TokenType::RBRACE, "}"}
    });

    novasyntax::Parser parser(tokens);
    auto ast = parser.parse();

    ASSERT_NE(ast, nullptr);
    
    // Check if it's a function declaration
    auto* func_decl = dynamic_cast<novasyntax::FunctionDeclaration*>(ast.get());
    ASSERT_NE(func_decl, nullptr);

    EXPECT_EQ(func_decl->name, "add");
    EXPECT_EQ(func_decl->parameters.size(), 2);
    EXPECT_EQ(func_decl->parameters[0], "x");
    EXPECT_EQ(func_decl->parameters[1], "y");

    // Check body is a simple expression
    auto* body_expr = dynamic_cast<novasyntax::Expression*>(func_decl->body.get());
    ASSERT_NE(body_expr, nullptr);
    EXPECT_EQ(body_expr->value, "x");
}

TEST(ParserTest, VariableDeclaration) {
    auto tokens = createTokens({
        {novasyntax::TokenType::LET, "let"},
        {novasyntax::TokenType::IDENTIFIER, "x"},
        {novasyntax::TokenType::ASSIGN, "="},
        {novasyntax::TokenType::NUMBER, "42"}
    });

    novasyntax::Parser parser(tokens);
    auto ast = parser.parse();

    ASSERT_NE(ast, nullptr);
    
    // Check if it's a variable declaration
    auto* var_decl = dynamic_cast<novasyntax::VariableDeclaration*>(ast.get());
    ASSERT_NE(var_decl, nullptr);

    EXPECT_EQ(var_decl->name, "x");
    ASSERT_NE(var_decl->initializer, nullptr);
    
    // Cast initializer to Expression to check value
    auto* expr = dynamic_cast<novasyntax::Expression*>(var_decl->initializer.get());
    ASSERT_NE(expr, nullptr);
    EXPECT_EQ(expr->value, "42");
}

TEST(ParserTest, SimpleExpression) {
    auto tokens = createTokens({
        {novasyntax::TokenType::NUMBER, "42"}
    });

    novasyntax::Parser parser(tokens);
    auto ast = parser.parse();

    ASSERT_NE(ast, nullptr);
    
    // Check if it's an expression
    auto* expr = dynamic_cast<novasyntax::Expression*>(ast.get());
    ASSERT_NE(expr, nullptr);

    EXPECT_EQ(expr->value, "42");
}

TEST(ParserTest, ErrorRecovery) {
    // Malformed input to test error recovery
    auto tokens = createTokens({
        {novasyntax::TokenType::FUNCTION, "func"},
        {novasyntax::TokenType::IDENTIFIER, "broken"},
        {novasyntax::TokenType::LPAREN, "("},
        {novasyntax::TokenType::RPAREN, ")"},
        {novasyntax::TokenType::ASSIGN, "="}  // Unexpected token
    });

    novasyntax::Parser parser(tokens);
    
    // Expect parser to handle error gracefully
    EXPECT_NO_THROW({
        auto ast = parser.parse();
        EXPECT_TRUE(ast == nullptr || 
            dynamic_cast<novasyntax::FunctionDeclaration*>(ast.get()) != nullptr);
    });
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
