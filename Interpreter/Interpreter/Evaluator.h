#pragma once
#include <memory>
#include <string>
#include "Node.h"
#include "Object.h"
#include "Environment.h"

class Evaluator {
private:
    std::shared_ptr<Object> NULL_OBJ;
    std::shared_ptr<Object> TRUE_OBJ;
    std::shared_ptr<Object> FALSE_OBJ;

    std::shared_ptr<Object> evalProgram(const Program* program, std::shared_ptr<Environment> env);
    std::shared_ptr<Object> evalBlockStatement(const BlockStatement* block, std::shared_ptr<Environment> env);
    std::shared_ptr<Object> evalPrefixExpression(const std::string& op, std::shared_ptr<Object> right);
    std::shared_ptr<Object> evalInfixExpression(const std::string& op, 
                                               std::shared_ptr<Object> left, 
                                               std::shared_ptr<Object> right);
    std::shared_ptr<Object> evalIfExpression(const IfExpression* ie, std::shared_ptr<Environment> env);
    std::shared_ptr<Object> evalIdentifier(const Identifier* node, std::shared_ptr<Environment> env);
    
    bool isTruthy(std::shared_ptr<Object> obj);
    bool isError(std::shared_ptr<Object> obj);
    std::shared_ptr<Object> newError(const std::string& message);

public:
    Evaluator();
    std::shared_ptr<Object> Eval(Node* node, std::shared_ptr<Environment> env);
};