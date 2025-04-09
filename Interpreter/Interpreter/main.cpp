#include <iostream>
#include "Lexer.h"
#include "token.h"

int main() {
  std::string input;
    std::cout << "Enter a string to tokenize: ";
    std::getline(std::cin, input);

    Lexer lexer(input, 0, 0, ' ');
    std::cout << "Input: " << input << "\n";

    Token token = lexer.NextToken();
    while (token.type != TokenType::END_OF_FILE) {
        std::cout << "Type: " << Token::tokenTypeToString(token.type)
                  << ", Literal: " << token.literal << "\n";
        token = lexer.NextToken();
    }

    return 0;
}
