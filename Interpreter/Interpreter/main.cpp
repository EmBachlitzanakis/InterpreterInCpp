#include "main.h"
#include <string>
#include <iostream>
#include "Lexer.h"
#include "token.h"

int main() {
    std::string input = "fn like 3";
    Lexer lexer(input,0,0, ' ');
	std::cout << "Input: " << input << std::endl;
    Token token = lexer.NextToken();
    while (token.type != TokenType::END_OF_FILE) {
        std::cout << "Type: " << Token::tokenTypeToString(token.type)
            << ", Literal: " << token.literal << std::endl;
        token = lexer.NextToken();
    }

    return 0; 
}
