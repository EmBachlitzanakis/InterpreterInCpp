#include "Identifier.h"

// Constructor
Identifier::Identifier( ::Token token,  std::string value)
    : Token(token), Value(value) {
}
// Destructor
Identifier::~Identifier() {}

void Identifier::expressionNode() {}

std::string Identifier::TokenLiteral() const {
    return Token.literal;
}

std::string Identifier::String() const {
    return Value;
}