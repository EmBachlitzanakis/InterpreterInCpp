#include "Identifier.h"

// Constructor
Identifier::Identifier(const ::Token& token, const std::string& value)
    : Token(token), Value(value) {
}
// Destructor
Identifier::~Identifier() {}

// Implementation of the Expression interface
void Identifier::expressionNode() {}

// Returns the literal value of the token
std::string Identifier::TokenLiteral() const {
    return Token.literal;
}

// Returns the string representation of the identifier
std::string Identifier::String() const {
    return Value;
}