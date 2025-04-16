#include "Boolean.h"

// Constructor
Boolean::Boolean( ::Token token,  bool value)
    : Token(token), Value(value) {
}
// Destructor
Boolean::~Boolean() {}

void Boolean::expressionNode() {}

std::string Boolean::TokenLiteral() const {
    return Token.literal;
}

std::string Boolean::String() const {
    return Token.literal;
}
