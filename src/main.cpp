#include <iostream>
#include <stdexcept>
#include "lexer.hpp"

int main() {
    std::string source = R"(
        func calculate(x, y) {
            let result = x + y
            let message = "Calculation complete"
            return result
        }
    )";

    try {
        novasyntax::Lexer lexer(source);
        auto tokens = lexer.tokenize();

        std::cout << "NovaSyntax Lexer Demo\n";
        std::cout << "--------------------\n";
        for (const auto& token : tokens) {
            std::cout << "Type: " << static_cast<int>(token.type) 
                      << ", Literal: " << token.literal 
                      << ", Line: " << token.line 
                      << ", Column: " << token.column << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Lexer Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
