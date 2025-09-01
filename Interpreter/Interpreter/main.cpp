#include <iostream>
#include "Lexer.h"
#include "token.h"

int main() {
    std::string input = R"(
        let five = 5;
        let ten = 10;
        let add = fn(x, y) {
            return x + y;
        };
        let result = add(five, ten);
    )";

    Lexer lexer(input, 0, 0, ' ');
    Parser parser(lexer);
    
    auto program = parser.ParseProgram();
    auto errors = parser.Errors();
    
    if (!errors.empty()) {
        std::cout << "Parser errors:\n";
        for (const auto& err : errors) {
            std::cout << "\t" << err << "\n";
        }
        return 1;
    }

    std::cout << "Program parsed successfully!\n";
    std::cout << "Program string representation:\n";
    std::cout << program->String() << "\n";

    return 0;
}