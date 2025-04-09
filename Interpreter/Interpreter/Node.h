#ifndef NODE_H
#define NODE_H

#include <string>

class Node {
public:
    virtual std::string TokenLiteral() const = 0;
    virtual std::string String() const = 0;
    virtual ~Node() {}
};

#endif

