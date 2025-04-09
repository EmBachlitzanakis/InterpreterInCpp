#include "Program.h"

Program::Program() : Statements() {}

Program::~Program() {
    for (Statement* stmt : Statements) {
        delete stmt;
    }
}

std::string Program::TokenLiteral() const {
    if (!Statements.empty()) {
        return Statements[0]->TokenLiteral();
    }
    else {
        return "";
    }
}

std::string Program::String() const {
    std::stringstream out;
    for (const Statement* s : Statements) {
        out << s->String();
    }
    return out.str();
}