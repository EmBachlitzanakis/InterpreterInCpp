#include "InfixExpression.h"




#include <sstream>



InfixExpression::InfixExpression(::Token token, std::string value, Expression* right, Expression* left)
    : Token(token), Operator(value), Right(right), Left(left) {
}
// Destructor
InfixExpression::~InfixExpression() {
    delete Right;
}

void InfixExpression::expressionNode() {}

std::string InfixExpression::TokenLiteral() const {
    return Token.literal;
}

std::string InfixExpression::String() const {

    std::stringstream out;
    out << "(" <<Left->String()<<" " << Operator <<" " << Right->String() << ")";
    return out.str();
}