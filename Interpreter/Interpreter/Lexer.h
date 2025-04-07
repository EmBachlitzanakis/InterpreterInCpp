#pragma once

#include <string>
#include "Helper.h"

class Lexer
{

public:
	std::string input;
	int position;
	int readPosition;
	char ch;


	Lexer(std::string input, int position, int readPosition, char ch);

	void readChar();
	void skipWhitespace();

	std::string readNumber();

	std::string readIdentifier();

	char peekChar();

};

