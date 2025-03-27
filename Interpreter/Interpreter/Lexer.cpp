#include "Lexer.h"

Lexer::Lexer(std::string input_str, int position, int readPosition, char current_ch)
    : input(input_str), position(position), readPosition(readPosition), ch(current_ch) {}



void Lexer::readChar() {
    if (readPosition >= input.length()) {
        ch = 0;
    }
    else {
        ch = input[readPosition];
    }
    position = readPosition;
    readPosition++;
}
void