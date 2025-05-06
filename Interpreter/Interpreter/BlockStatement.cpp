#include "BlockStatement.h"
#include <sstream>

BlockStatement::BlockStatement(const Token& token) : token_(token) {
}

void BlockStatement::AddStatement(Statement* statement) {
    statements_.push_back(statement);
}

const std::vector<Statement*>& BlockStatement::GetStatements() const {
    return statements_;
}

void BlockStatement::statementNode() {
    // Empty implementation as per the Go code
}

std::string BlockStatement::TokenLiteral() const {
    return token_.literal;
}

std::string BlockStatement::String() const {
    std::stringstream out;

    for (const auto& s : statements_) {
        out << s->String();
    }

    return out.str();
}

BlockStatement::~BlockStatement() {
    // Clean up owned statements
    for (auto s : statements_) {
        delete s;
    }
}