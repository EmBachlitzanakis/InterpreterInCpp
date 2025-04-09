#ifndef TOKEN_H
#define TOKEN_H

#include <string>

// Define the TokenType enum BEFORE the Token class
enum class TokenType {
    ILLEGAL,
    END_OF_FILE,
    IDENT,
    INT,
    ASSIGN,
    PLUS,
    MINUS,
    ASTERISK,
    SLASH,
    BANG,
    EQ,
    NOT_EQ,
    LT,
    GT,
    COMMA,
    SEMICOLON,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    FUNCTION,
    LET,
    TRUE,
    FALSE,
    IF,
    ELSE,
    RETURN
};

class Token {
public:
    TokenType type;
    std::string literal;

    Token(TokenType type, std::string literal);
    static std::string tokenTypeToString(TokenType type);
    static TokenType lookupIdent(const std::string& ident);
};

#endif // TOKEN_H


