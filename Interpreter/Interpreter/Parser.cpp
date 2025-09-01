#include "Parser.h"
#include <algorithm>

Parser::Parser(Lexer& l) : lexer(l) {
    // Read two tokens so currentToken and peekToken are set
    nextToken();
    nextToken();

    // Register prefix parse functions
    registerPrefix(TokenType::IDENT, [this]() { return parseIdentifier(); });
    registerPrefix(TokenType::INT, [this]() { return parseIntegerLiteral(); });
    registerPrefix(TokenType::BANG, [this]() { return parsePrefixExpression(); });
    registerPrefix(TokenType::MINUS, [this]() { return parsePrefixExpression(); });
    registerPrefix(TokenType::TRUE, [this]() { return parseBoolean(); });
    registerPrefix(TokenType::FALSE, [this]() { return parseBoolean(); });
    registerPrefix(TokenType::LPAREN, [this]() { return parseGroupedExpression(); });
    registerPrefix(TokenType::IF, [this]() { return parseIfExpression(); });
    registerPrefix(TokenType::FUNCTION, [this]() { return parseFunctionLiteral(); });

    // Register infix parse functions
    registerInfix(TokenType::PLUS, [this](std::unique_ptr<Expression> left) { return parseInfixExpression(std::move(left)); });
    registerInfix(TokenType::MINUS, [this](std::unique_ptr<Expression> left) { return parseInfixExpression(std::move(left)); });
    registerInfix(TokenType::SLASH, [this](std::unique_ptr<Expression> left) { return parseInfixExpression(std::move(left)); });
    registerInfix(TokenType::ASTERISK, [this](std::unique_ptr<Expression> left) { return parseInfixExpression(std::move(left)); });
    registerInfix(TokenType::EQ, [this](std::unique_ptr<Expression> left) { return parseInfixExpression(std::move(left)); });
    registerInfix(TokenType::NOT_EQ, [this](std::unique_ptr<Expression> left) { return parseInfixExpression(std::move(left)); });
    registerInfix(TokenType::LT, [this](std::unique_ptr<Expression> left) { return parseInfixExpression(std::move(left)); });
    registerInfix(TokenType::GT, [this](std::unique_ptr<Expression> left) { return parseInfixExpression(std::move(left)); });
    registerInfix(TokenType::LPAREN, [this](std::unique_ptr<Expression> function) { return parseCallExpression(std::move(function)); });

    // Register precedences
    registerPrecedence(TokenType::EQ, Precedence::EQUALS);
    registerPrecedence(TokenType::NOT_EQ, Precedence::EQUALS);
    registerPrecedence(TokenType::LT, Precedence::LESSGREATER);
    registerPrecedence(TokenType::GT, Precedence::LESSGREATER);
    registerPrecedence(TokenType::PLUS, Precedence::SUM);
    registerPrecedence(TokenType::MINUS, Precedence::SUM);
    registerPrecedence(TokenType::SLASH, Precedence::PRODUCT);
    registerPrecedence(TokenType::ASTERISK, Precedence::PRODUCT);
    registerPrecedence(TokenType::LPAREN, Precedence::CALL);
}

void Parser::nextToken() {
    currentToken = peekToken;
    peekToken = lexer.NextToken();
}

std::unique_ptr<Program> Parser::ParseProgram() {
    auto program = std::make_unique<Program>();
    
    while (currentToken.type != TokenType::END_OF_FILE) {
        auto stmt = parseStatement();
        if (stmt) {
            program->statements.push_back(std::move(stmt));
        }
        nextToken();
    }
    
    return program;
}

std::unique_ptr<Statement> Parser::parseStatement() {
    switch (currentToken.type) {
        case TokenType::LET:
            return parseLetStatement();
        case TokenType::RETURN:
            return parseReturnStatement();
        default:
            return parseExpressionStatement();
    }
}

std::unique_ptr<Statement> Parser::parseLetStatement() {
    auto stmt = std::make_unique<LetStatement>();
    stmt->token = currentToken;

    if (!expectPeek(TokenType::IDENT)) {
        return nullptr;
    }

    stmt->name = std::make_unique<Identifier>(currentToken, currentToken.literal);

    if (!expectPeek(TokenType::ASSIGN)) {
        return nullptr;
    }

    nextToken();

    stmt->value = parseExpression(Precedence::LOWEST);

    if (peekTokenIs(TokenType::SEMICOLON)) {
        nextToken();
    }

    return stmt;
}

std::unique_ptr<Statement> Parser::parseReturnStatement() {
    auto stmt = std::make_unique<ReturnStatement>();
    stmt->token = currentToken;

    nextToken();

    stmt->returnValue = parseExpression(Precedence::LOWEST);

    if (peekTokenIs(TokenType::SEMICOLON)) {
        nextToken();
    }

    return stmt;
}

std::unique_ptr<Statement> Parser::parseExpressionStatement() {
    auto stmt = std::make_unique<ExpressionStatement>();
    stmt->token = currentToken;
    
    stmt->expression = parseExpression(Precedence::LOWEST);

    if (peekTokenIs(TokenType::SEMICOLON)) {
        nextToken();
    }

    return stmt;
}

std::unique_ptr<Expression> Parser::parseExpression(Precedence precedence) {
    auto prefix = prefixParseFns.find(currentToken.type);
    if (prefix == prefixParseFns.end()) {
        errors.push_back("no prefix parse function for " + Token::tokenTypeToString(currentToken.type) + " found");
        return nullptr;
    }

    auto leftExp = prefix->second();

    while (!peekTokenIs(TokenType::SEMICOLON) && precedence < peekPrecedence()) {
        auto infix = infixParseFns.find(peekToken.type);
        if (infix == infixParseFns.end()) {
            return leftExp;
        }

        nextToken();
        leftExp = infix->second(std::move(leftExp));
    }

    return leftExp;
}

// Helper methods
bool Parser::curTokenIs(TokenType t) {
    return currentToken.type == t;
}

bool Parser::peekTokenIs(TokenType t) {
    return peekToken.type == t;
}

bool Parser::expectPeek(TokenType t) {
    if (peekTokenIs(t)) {
        nextToken();
        return true;
    }
    errors.push_back("expected next token to be " + Token::tokenTypeToString(t) + 
                    ", got " + Token::tokenTypeToString(peekToken.type) + " instead");
    return false;
}

void Parser::registerPrefix(TokenType tokenType, PrefixParseFn fn) {
    prefixParseFns[tokenType] = std::move(fn);
}

void Parser::registerInfix(TokenType tokenType, InfixParseFn fn) {
    infixParseFns[tokenType] = std::move(fn);
}

void Parser::registerPrecedence(TokenType tokenType, Precedence precedence) {
    precedences[tokenType] = precedence;
}

Precedence Parser::peekPrecedence() {
    if (auto it = precedences.find(peekToken.type); it != precedences.end()) {
        return it->second;
    }
    return Precedence::LOWEST;
}

Precedence Parser::curPrecedence() {
    if (auto it = precedences.find(currentToken.type); it != precedences.end()) {
        return it->second;
    }
    return Precedence::LOWEST;
}

const std::vector<std::string>& Parser::Errors() const {
    return errors;
}

std::unique_ptr<Expression> Parser::parseIdentifier() {
    return std::make_unique<Identifier>(currentToken, currentToken.literal);
}

std::unique_ptr<Expression> Parser::parseIntegerLiteral() {
    try {
        int value = std::stoi(currentToken.literal);
        return std::make_unique<IntegerLiteral>(currentToken, value);
    } catch (const std::exception&) {
        errors.push_back("could not parse " + currentToken.literal + " as integer");
        return nullptr;
    }
}

std::unique_ptr<Expression> Parser::parsePrefixExpression() {
    auto expression = std::make_unique<PrefixExpression>();
    expression->token = currentToken;
    expression->op = currentToken.literal;

    nextToken();

    expression->right = parseExpression(Precedence::PREFIX);
    return expression;
}

std::unique_ptr<Expression> Parser::parseInfixExpression(std::unique_ptr<Expression> left) {
    auto expression = std::make_unique<InfixExpression>();
    expression->token = currentToken;
    expression->op = currentToken.literal;
    expression->left = std::move(left);

    auto precedence = curPrecedence();
    nextToken();
    expression->right = parseExpression(precedence);

    return expression;
}

std::unique_ptr<Expression> Parser::parseBoolean() {
    return std::make_unique<Boolean>(currentToken, curTokenIs(TokenType::TRUE));
}

std::unique_ptr<Expression> Parser::parseGroupedExpression() {
    nextToken();

    auto exp = parseExpression(Precedence::LOWEST);

    if (!expectPeek(TokenType::RPAREN)) {
        return nullptr;
    }

    return exp;
}

std::unique_ptr<Expression> Parser::parseIfExpression() {
    auto expression = std::make_unique<IfExpression>();
    expression->token = currentToken;

    if (!expectPeek(TokenType::LPAREN)) {
        return nullptr;
    }

    nextToken();
    expression->condition = parseExpression(Precedence::LOWEST);

    if (!expectPeek(TokenType::RPAREN)) {
        return nullptr;
    }

    if (!expectPeek(TokenType::LBRACE)) {
        return nullptr;
    }

    expression->consequence = parseBlockStatement();

    if (peekTokenIs(TokenType::ELSE)) {
        nextToken();

        if (!expectPeek(TokenType::LBRACE)) {
            return nullptr;
        }

        expression->alternative = parseBlockStatement();
    }

    return expression;
}

std::unique_ptr<BlockStatement> Parser::parseBlockStatement() {
    auto block = std::make_unique<BlockStatement>();
    block->token = currentToken;

    nextToken();

    while (!curTokenIs(TokenType::RBRACE) && !curTokenIs(TokenType::END_OF_FILE)) {
        auto stmt = parseStatement();
        if (stmt) {
            block->statements.push_back(std::move(stmt));
        }
        nextToken();
    }

    return block;
}

std::unique_ptr<Expression> Parser::parseFunctionLiteral() {
    auto lit = std::make_unique<FunctionLiteral>();
    lit->token = currentToken;

    if (!expectPeek(TokenType::LPAREN)) {
        return nullptr;
    }

    lit->parameters = parseFunctionParameters();

    if (!expectPeek(TokenType::LBRACE)) {
        return nullptr;
    }

    lit->body = parseBlockStatement();

    return lit;
}

std::vector<std::unique_ptr<Identifier>> Parser::parseFunctionParameters() {
    std::vector<std::unique_ptr<Identifier>> parameters;

    if (peekTokenIs(TokenType::RPAREN)) {
        nextToken();
        return parameters;
    }

    nextToken();

    auto ident = std::make_unique<Identifier>(currentToken, currentToken.literal);
    parameters.push_back(std::move(ident));

    while (peekTokenIs(TokenType::COMMA)) {
        nextToken();
        nextToken();
        auto ident = std::make_unique<Identifier>(currentToken, currentToken.literal);
        parameters.push_back(std::move(ident));
    }

    if (!expectPeek(TokenType::RPAREN)) {
        return std::vector<std::unique_ptr<Identifier>>();
    }

    return parameters;
}

std::unique_ptr<Expression> Parser::parseCallExpression(std::unique_ptr<Expression> function) {
    auto exp = std::make_unique<CallExpression>();
    exp->token = currentToken;
    exp->function = std::move(function);
    exp->arguments = parseExpressionList(TokenType::RPAREN);
    return exp;
}

std::vector<std::unique_ptr<Expression>> Parser::parseExpressionList(TokenType end) {
    std::vector<std::unique_ptr<Expression>> list;

    if (peekTokenIs(end)) {
        nextToken();
        return list;
    }

    nextToken();
    list.push_back(parseExpression(Precedence::LOWEST));

    while (peekTokenIs(TokenType::COMMA)) {
        nextToken();
        nextToken();
        list.push_back(parseExpression(Precedence::LOWEST));
    }

    if (!expectPeek(end)) {
        return std::vector<std::unique_ptr<Expression>>();
    }

    return list;
}
