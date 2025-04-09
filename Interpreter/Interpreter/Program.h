// Program.h
#ifndef PROGRAM_H
#define PROGRAM_H

#include <vector>
#include <string>
#include <sstream> 
#include <iostream>
#include "Statement.h"

class Program {
public:
    std::vector<Statement*> Statements;

    Program() : Statements() {}

    ~Program() {}

    // C++ equivalent of Go's TokenLiteral()
    std::string TokenLiteral() const;

    // C++ equivalent of Go's String()
    std::string String() const;
};

#endif