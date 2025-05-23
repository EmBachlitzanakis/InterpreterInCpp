#include "FunctionLiteral.h"
#include <sstream>

FunctionLiteral::FunctionLiteral(
    const Token& token,
    const std::vector<std::shared_ptr<Identifier>>& parameters,
    std::shared_ptr<BlockStatement> body)
    : token(token),
    parameters(parameters),
    body(body) {
}

void FunctionLiteral::expressionNode() {
    // Empty implementation as in the Go code
}

std::string FunctionLiteral::TokenLiteral() const {
    return token.literal;
}

std::string FunctionLiteral::String() const {
    std::ostringstream out;

    // Convert parameters to strings
    std::vector<std::string> paramStrs;
    for (const auto& p : parameters) {
        paramStrs.push_back(p->String());
    }

    // Join parameters with comma
    std::string paramsStr;
    for (size_t i = 0; i < paramStrs.size(); i++) {
        if (i > 0) paramsStr += ", ";
        paramsStr += paramStrs[i];
    }

    out << TokenLiteral();
    out << "(";
    out << paramsStr;
    out << ") ";
    out << body->String();

    return out.str();
}