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
std::string Lexer::readNumber() {
	Helper checker;
	std::string number;
	while (checker.isDigit(ch)) {
		number += ch;
		readChar();
	}
	return number;
}

std::string Lexer::readIdentifier() {
	Helper checker;
	std::string identifier;
	while (checker.isLetter(ch)) {
		identifier += ch;
		readChar();
	}
	return identifier;
}

void Lexer::skipWhitespace() {
	Helper checker;
	while (checker.isWhitespace(ch)) {
		readChar();
	}
	
}

char Lexer::peekChar() {
	if (readPosition >= input.length()) {
		return '\0';
	}
	else {
		return input[readPosition];
	}
}