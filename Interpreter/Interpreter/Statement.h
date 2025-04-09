#ifndef STATEMENT_H
#define STATEMENT_H

#include "Node.h" // Statement inherits from Node

class Statement : public Node {
public:
    virtual void statementNode() = 0;
    virtual ~Statement() {}
};

#endif