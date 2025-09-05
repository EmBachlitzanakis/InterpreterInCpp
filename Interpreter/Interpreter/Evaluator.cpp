#include "Evaluator.h"
#include "Object.h"
#include <format>

Evaluator::Evaluator() {
    NULL_OBJ = std::make_shared<NullObject>();
    TRUE_OBJ = std::make_shared<Boolean>(true);
    FALSE_OBJ = std::make_shared<Boolean>(false);
}

std::shared_ptr<Object> Evaluator::Eval(Node* node, std::shared_ptr<Environment> env) {
    if (auto program = dynamic_cast<Program*>(node)) {
        return evalProgram(program, env);
    }
    
    if (auto expr = dynamic_cast<ExpressionStatement*>(node)) {
        return Eval(expr->expression.get(), env);
    }
    
    if (auto integer = dynamic_cast<IntegerLiteral*>(node)) {
        return std::make_shared<Integer>(integer->value);
    }
    
    if (auto boolean = dynamic_cast<Boolean*>(node)) {
        return boolean->value ? TRUE_OBJ : FALSE_OBJ;
    }
    
    if (auto prefix = dynamic_cast<PrefixExpression*>(node)) {
        auto right = Eval(prefix->right.get(), env);
        if (isError(right)) return right;
        return evalPrefixExpression(prefix->op, right);
    }

    // Add more cases as needed...
    
    return NULL_OBJ;
}

std::shared_ptr<Object> Evaluator::evalProgram(const Program* program, std::shared_ptr<Environment> env) {
    std::shared_ptr<Object> result;
    
    for (const auto& stmt : program->statements) {
        result = Eval(stmt.get(), env);
        
        if (auto returnValue = std::dynamic_pointer_cast<ReturnValue>(result)) {
            return returnValue->value;
        }
        
        if (auto error = std::dynamic_pointer_cast<Error>(result)) {
            return result;
        }
    }
    
    return result;
}