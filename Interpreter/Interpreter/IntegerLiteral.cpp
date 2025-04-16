#include "IntegerLiteral.h"

// Constructor
IntegerLiteral::IntegerLiteral( ::Token& token,  int value)
    : Token(token), Value(value) {
}
// Destructor
IntegerLiteral::~IntegerLiteral() {}

void IntegerLiteral::expressionNode() {}

std::string IntegerLiteral::TokenLiteral() const {
    return Token.literal;
}

std::string IntegerLiteral::String() const {
    return Token.literal;
}
