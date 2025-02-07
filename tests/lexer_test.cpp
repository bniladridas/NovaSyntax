#include <gtest/gtest.h>
#include "lexer.hpp"

TEST(LexerTest, BasicTokenization) {
    std::string source = "func calculate(x, y) { let result = x + y }";
    novasyntax::Lexer lexer(source);
    auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 10); // 9 tokens + EOF
    EXPECT_EQ(tokens[0].type, novasyntax::TokenType::FUNCTION);
    EXPECT_EQ(tokens[1].type, novasyntax::TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[2].type, novasyntax::TokenType::LPAREN);
    EXPECT_EQ(tokens[3].type, novasyntax::TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[4].type, novasyntax::TokenType::COMMA);
    EXPECT_EQ(tokens[5].type, novasyntax::TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[6].type, novasyntax::TokenType::RPAREN);
    EXPECT_EQ(tokens[7].type, novasyntax::TokenType::LBRACE);
    EXPECT_EQ(tokens[8].type, novasyntax::TokenType::LET);
}

TEST(LexerTest, StringTokenization) {
    std::string source = R"(let message = "Hello, NovaSyntax!")";
    novasyntax::Lexer lexer(source);
    auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 5); // 4 tokens + EOF
    EXPECT_EQ(tokens[0].type, novasyntax::TokenType::LET);
    EXPECT_EQ(tokens[1].type, novasyntax::TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[2].type, novasyntax::TokenType::ASSIGN);
    EXPECT_EQ(tokens[3].type, novasyntax::TokenType::STRING);
    EXPECT_EQ(tokens[3].literal, "Hello, NovaSyntax!");
}

TEST(LexerTest, NumberTokenization) {
    std::string source = "let x = 42.5";
    novasyntax::Lexer lexer(source);
    auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 5); // 4 tokens + EOF
    EXPECT_EQ(tokens[0].type, novasyntax::TokenType::LET);
    EXPECT_EQ(tokens[1].type, novasyntax::TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[2].type, novasyntax::TokenType::ASSIGN);
    EXPECT_EQ(tokens[3].type, novasyntax::TokenType::NUMBER);
    EXPECT_EQ(tokens[3].literal, "42.5");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
