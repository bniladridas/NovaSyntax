#include <gtest/gtest.h>
#include "lexer.hpp"

TEST(LexerTest, BasicTokenization) {
    std::string source = "func add(x, y) { return x + y }";
    novasyntax::Lexer lexer(source);
    auto tokens = lexer.tokenize();

    // Detailed token type checking
    std::vector<std::pair<novasyntax::TokenType, std::string>> expectedTokens = {
        {novasyntax::TokenType::FUNCTION, "func"},
        {novasyntax::TokenType::IDENTIFIER, "add"},
        {novasyntax::TokenType::LPAREN, "("},
        {novasyntax::TokenType::IDENTIFIER, "x"},
        {novasyntax::TokenType::COMMA, ","},
        {novasyntax::TokenType::IDENTIFIER, "y"},
        {novasyntax::TokenType::RPAREN, ")"},
        {novasyntax::TokenType::LBRACE, "{"},
        {novasyntax::TokenType::RETURN, "return"},
        {novasyntax::TokenType::IDENTIFIER, "x"},
        {novasyntax::TokenType::PLUS, "+"},
        {novasyntax::TokenType::IDENTIFIER, "y"},
        {novasyntax::TokenType::RBRACE, "}"},
        {novasyntax::TokenType::EOF_, "<EOF>"}
    };

    // Detailed token printing
    std::cout << "Source string: '" << source << "'" << std::endl;
    std::cout << "Source length: " << source.length() << std::endl;
    std::cout << "Token Count: " << tokens.size() << std::endl;
    
    // Print all tokens with detailed information
    for (size_t i = 0; i < tokens.size(); ++i) {
        std::cout << "Token " << i 
                  << ": Type=" << static_cast<int>(tokens[i].type) 
                  << ", Literal='" << tokens[i].literal 
                  << "', Line=" << tokens[i].line 
                  << ", Column=" << tokens[i].column 
                  << std::endl;
    }

    // Print expected tokens
    std::cout << "\nExpected Tokens:" << std::endl;
    for (size_t i = 0; i < expectedTokens.size(); ++i) {
        std::cout << "Expected Token " << i 
                  << ": Type=" << static_cast<int>(expectedTokens[i].first) 
                  << ", Literal='" << expectedTokens[i].second 
                  << "'" << std::endl;
    }

    // Verify token count
    ASSERT_EQ(tokens.size(), 14);

    // Check each token type and literal
    for (size_t i = 0; i < expectedTokens.size(); ++i) {
        EXPECT_EQ(tokens[i].type, expectedTokens[i].first) 
            << "Mismatch at token " << i 
            << ", Expected Type: " << static_cast<int>(expectedTokens[i].first) 
            << ", Got Type: " << static_cast<int>(tokens[i].type);
        
        EXPECT_EQ(tokens[i].literal, expectedTokens[i].second)
            << "Mismatch at token " << i 
            << ", Expected Literal: '" << expectedTokens[i].second 
            << "', Got Literal: '" << tokens[i].literal << "'";
    }
}

TEST(LexerTest, StringTokenization) {
    std::string source = "let message = \"Hello, NovaSyntax!\"";
    novasyntax::Lexer lexer(source);
    auto tokens = lexer.tokenize();

    std::vector<std::pair<novasyntax::TokenType, std::string>> expectedTokens = {
        {novasyntax::TokenType::LET, "let"},
        {novasyntax::TokenType::IDENTIFIER, "message"},
        {novasyntax::TokenType::ASSIGN, "="},
        {novasyntax::TokenType::STRING, "Hello, NovaSyntax!"},
        {novasyntax::TokenType::EOF_, "<EOF>"}
    };

    ASSERT_EQ(tokens.size(), expectedTokens.size());
    for (size_t i = 0; i < expectedTokens.size(); ++i) {
        EXPECT_EQ(tokens[i].type, expectedTokens[i].first);
        EXPECT_EQ(tokens[i].literal, expectedTokens[i].second);
    }
}

TEST(LexerTest, NumberTokenization) {
    std::string source = "let x = 42.5";
    novasyntax::Lexer lexer(source);
    auto tokens = lexer.tokenize();

    std::vector<std::pair<novasyntax::TokenType, std::string>> expectedTokens = {
        {novasyntax::TokenType::LET, "let"},
        {novasyntax::TokenType::IDENTIFIER, "x"},
        {novasyntax::TokenType::ASSIGN, "="},
        {novasyntax::TokenType::NUMBER, "42.5"},
        {novasyntax::TokenType::EOF_, "<EOF>"}
    };

    ASSERT_EQ(tokens.size(), expectedTokens.size());
    for (size_t i = 0; i < expectedTokens.size(); ++i) {
        EXPECT_EQ(tokens[i].type, expectedTokens[i].first);
        EXPECT_EQ(tokens[i].literal, expectedTokens[i].second);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}