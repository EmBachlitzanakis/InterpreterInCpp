#pragma once
#include <string>
#include <memory>

enum class ObjectType {
    INTEGER,
    BOOLEAN,
    NULL_OBJ,
    RETURN_VALUE,
    ERROR,
    FUNCTION
};

class Object {
public:
    virtual ~Object() = default;
    virtual ObjectType Type() const = 0;
    virtual std::string Inspect() const = 0;
};

class Integer : public Object {
public:
    int64_t value;
    
    explicit Integer(int64_t v) : value(v) {}
    ObjectType Type() const override { return ObjectType::INTEGER; }
    std::string Inspect() const override { return std::to_string(value); }
};

class