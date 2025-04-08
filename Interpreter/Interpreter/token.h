#ifndef TOKEN_H
#define TOKEN_H

#include <string>

// Define the TokenType enum BEFORE the Token class
enum class TokenType {
    ILLEGAL,
    END_OF_FILE,

    // Identifiers + literals
    IDENT,
    INT,
    // STRING,

    // Operators
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

    // Delimiters
    COMMA,
    SEMICOLON,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,

    // Keywords
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


