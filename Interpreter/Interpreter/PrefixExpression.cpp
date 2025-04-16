#include "PrefixExpression.h"

#include <sstream>



PrefixExpression::PrefixExpression(::Token token, std::string value , Expression* right)
    : Token(token), Operator(value), Right(right) {
}
// Destructor
PrefixExpression::~PrefixExpression() {
	delete Right;
}

void PrefixExpression::expressionNode() {}

std::string PrefixExpression::TokenLiteral() const {
    return Token.literal;
}

std::string PrefixExpression::String() const {

        std::stringstream out;
        out << "(" << Operator << Right->String() << ")";
        return out.str();
}
