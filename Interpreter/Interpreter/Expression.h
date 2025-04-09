#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "Node.h" // Expression inherits from Node

class Expression : public Node {
public:
    virtual void expressionNode() = 0;
    virtual ~Expression() {}
};

#endif
