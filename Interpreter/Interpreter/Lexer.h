#pragma once

#include <string>
#include "Helper.h"
#include "token.h"


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

	Token NextToken();

	char peekChar();
	Token newToken(TokenType type, char literal);

};

