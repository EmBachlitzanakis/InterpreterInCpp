#include "Lexer.h"

Lexer::Lexer(std::string input_str, int position, int readPosition, char current_ch)
    : input(input_str), position(position), readPosition(readPosition), ch(current_ch) {}



void Lexer::readChar() {  
   if (readPosition >= static_cast<int>(input.length())) {  
       ch = '\0'; 
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

Token Lexer::NextToken() {
    Helper checker;
    Token tok(TokenType::ILLEGAL, "");

    skipWhitespace();

    switch (ch) {
    case '=':
        if (peekChar() == '=') {
            char current_ch = ch;
            readChar();
            tok = Token(TokenType::EQ, std::string(1, current_ch) + std::string(1, ch));
        }
        else {
            tok = newToken(TokenType::ASSIGN, ch);
        }
        break;
    case '+':
        tok = newToken(TokenType::PLUS, ch);
        break;
    case '-':
        tok = newToken(TokenType::MINUS, ch);
        break;
    case '!':
        if (peekChar() == '=') {
            char current_ch = ch;
            readChar();
            tok = Token(TokenType::NOT_EQ, std::string(1, current_ch) + std::string(1, ch));
        }
        else {
            tok = newToken(TokenType::BANG, ch);
        }
        break;
    case '/':
        tok = newToken(TokenType::SLASH, ch);
        break;
    case '*':
        tok = newToken(TokenType::ASTERISK, ch);
        break;
    case '<':
        tok = newToken(TokenType::LT, ch);
        break;
    case '>':
        tok = newToken(TokenType::GT, ch);
        break;
    case ';':
        tok = newToken(TokenType::SEMICOLON, ch);
        break;
    case ',':
        tok = newToken(TokenType::COMMA, ch);
        break;
    case '{':
        tok = newToken(TokenType::LBRACE, ch);
        break;
    case '}':
        tok = newToken(TokenType::RBRACE, ch);
        break;
    case '(':
        tok = newToken(TokenType::LPAREN, ch);
        break;
    case ')':
        tok = newToken(TokenType::RPAREN, ch);
        break;
    case '\0':
        tok = Token(TokenType::END_OF_FILE, "");
        break;
    default:
        if (checker.isLetter(ch)) {
            std::string identifier = readIdentifier();
            tok = Token(Token::lookupIdent(identifier), identifier);
            return tok;
        }
        else if (checker.isDigit(ch)) {
            std::string number = readNumber();
            tok = Token(TokenType::INT, number);
            return tok;
        }
        else {
            tok = newToken(TokenType::ILLEGAL, ch);
        }
    }

    readChar();
    return tok;
}

Token Lexer::newToken(TokenType type, char literal) {
    return Token(type, std::string(1, literal));
}