#pragma once

#include "Lexer.h"
#include "Program.h"
#include "Expression.h"
#include "Statement.h"
#include "LetStatement.h"
#include "ReturnStatement.h"
#include "ExpressionStatement.h"
#include "IntegerLiteral.h"
#include "PrefixExpression.h"
#include "InfixExpression.h"
#include "Boolean.h"
#include "IfExpression.h"
#include "FunctionLiteral.h"
#include "CallExpression.h"
#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>

enum class Precedence {
    LOWEST,
    EQUALS,      // ==
    LESSGREATER, // > or <
    SUM,         // +
    PRODUCT,     // *
    PREFIX,      // -X or !X
    CALL         // myFunction(X)
};

class Parser {
private:
    Lexer& lexer;
    Token currentToken;
    Token peekToken;
    std::vector<std::string> errors;

    // Function type definitions for prefix and infix parsing functions
    using PrefixParseFn = std::function<std::unique_ptr<Expression>()>;
    using InfixParseFn = std::function<std::unique_ptr<Expression>(std::unique_ptr<Expression>)>;

    std::unordered_map<TokenType, PrefixParseFn> prefixParseFns;
    std::unordered_map<TokenType, InfixParseFn> infixParseFns;
    std::unordered_map<TokenType, Precedence> precedences;

    // Token processing
    void nextToken();
    bool expectPeek(TokenType t);
    bool curTokenIs(TokenType t);
    bool peekTokenIs(TokenType t);
    Precedence peekPrecedence();
    Precedence curPrecedence();

    // Parsing helpers
    std::unique_ptr<Statement> parseStatement();
    std::unique_ptr<Statement> parseLetStatement();
    std::unique_ptr<Statement> parseReturnStatement();
    std::unique_ptr<Statement> parseExpressionStatement();
    std::unique_ptr<BlockStatement> parseBlockStatement();

    // Expression parsing
    std::unique_ptr<Expression> parseExpression(Precedence precedence);
    std::unique_ptr<Expression> parseIdentifier();
    std::unique_ptr<Expression> parseIntegerLiteral();
    std::unique_ptr<Expression> parsePrefixExpression();
    std::unique_ptr<Expression> parseInfixExpression(std::unique_ptr<Expression> left);
    std::unique_ptr<Expression> parseBoolean();
    std::unique_ptr<Expression> parseGroupedExpression();
    std::unique_ptr<Expression> parseIfExpression();
    std::unique_ptr<Expression> parseFunctionLiteral();
    std::unique_ptr<Expression> parseCallExpression(std::unique_ptr<Expression> function);
    std::vector<std::unique_ptr<Expression>> parseExpressionList(TokenType end);
    std::vector<std::unique_ptr<Identifier>> parseFunctionParameters();

    void registerPrefix(TokenType tokenType, PrefixParseFn fn);
    void registerInfix(TokenType tokenType, InfixParseFn fn);
    void registerPrecedence(TokenType tokenType, Precedence precedence);

public:
    explicit Parser(Lexer& l);
    std::unique_ptr<Program> ParseProgram();
    const std::vector<std::string>& Errors() const;
};
