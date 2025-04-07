#include "token.h"
#include <string>
#include <unordered_map>

std::string tokenTypeToString(TokenType type) {
    switch (type) {
    case TokenType::ILLEGAL: return "ILLEGAL";
    case TokenType::END_OF_FILE: return "EOF";
    case TokenType::IDENT: return "IDENT";
    case TokenType::INT: return "INT";
    case TokenType::ASSIGN: return "=";
    case TokenType::PLUS: return "+";
    case TokenType::MINUS: return "-";
    case TokenType::BANG: return "!";
    case TokenType::ASTERISK: return "*";
    case TokenType::SLASH: return "/";
    case TokenType::LT: return "<";
    case TokenType::GT: return ">";
    case TokenType::EQ: return "==";
    case TokenType::NOT_EQ: return "!=";
    case TokenType::COMMA: return ",";
    case TokenType::SEMICOLON: return ";";
    case TokenType::LPAREN: return "(";
    case TokenType::RPAREN: return ")";
    case TokenType::LBRACE: return "{";
    case TokenType::RBRACE: return "}";
    case TokenType::FUNCTION: return "FUNCTION";
    case TokenType::LET: return "LET";
    case TokenType::TRUE: return "TRUE";
    case TokenType::FALSE: return "FALSE";
    case TokenType::IF: return "IF";
    case TokenType::ELSE: return "ELSE";
    case TokenType::RETURN: return "RETURN";
    default: return "UNKNOWN";
    }
}

Token::Token(TokenType type, std::string literal) : type(type), literal(literal) {}

static const std::unordered_map<std::string, TokenType> keywords = {
    {"fn", TokenType::FUNCTION},
    {"let", TokenType::LET},
    {"true", TokenType::TRUE},
    {"false", TokenType::FALSE},
    {"if", TokenType::IF},
    {"else", TokenType::ELSE},
    {"return", TokenType::RETURN}
};

TokenType lookupIdent(const std::string& ident) {
    auto it = keywords.find(ident);
    if (it != keywords.end()) {
        return it->second;
    }
    return TokenType::IDENT;
}