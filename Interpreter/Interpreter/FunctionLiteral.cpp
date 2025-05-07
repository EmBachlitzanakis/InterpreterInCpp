#include "FunctionLiteral.h"
#include <sstream>

FunctionLiteral::FunctionLiteral(const Token& token) : token_(token), body_(nullptr) {
}

FunctionLiteral::~FunctionLiteral() {
    // Clean up parameters
    for (auto param : parameters_) {
        delete param;
    }

    // Clean up body if it exists and we own it
    delete body_;
}

void FunctionLiteral::AddParameter(Identifier* parameter) {
    parameters_.push_back(parameter);
}

void FunctionLiteral::SetBody(BlockStatement* body) {
    body_ = body;
}

const std::vector<Identifier*>& FunctionLiteral::GetParameters() const {
    return parameters_;
}

BlockStatement* FunctionLiteral::GetBody() const {
    return body_;
}

void FunctionLiteral::expressionNode() {
}

std::string FunctionLiteral::TokenLiteral() const {
    return token_.literal;
}

std::string FunctionLiteral::String() const {
    std::stringstream out;

    // Build parameters string
    std::vector<std::string> params;
    for (const auto& p : parameters_) {
        params.push_back(p->String());
    }

    // Join parameters with comma and space
    std::string paramsStr;
    for (size_t i = 0; i < params.size(); ++i) {
        if (i > 0) {
            paramsStr += ", ";
        }
        paramsStr += params[i];
    }

    out << TokenLiteral() << "(" << paramsStr << ") ";

    if (body_) {
        out << body_->String();
    }

    return out.str();
}