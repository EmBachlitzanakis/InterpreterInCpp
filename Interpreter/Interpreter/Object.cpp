#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "Object.h"

class Environment : public std::enable_shared_from_this<Environment> {
private:
    std::unordered_map<std::string, std::shared_ptr<Object>> store;
    std::shared_ptr<Environment> outer;

public:
    Environment() : outer(nullptr) {}
    explicit Environment(std::shared_ptr<Environment> o) : outer(o) {}

    std::shared_ptr<Object> Get(const std::string& name) {
        auto it = store.find(name);
        if (it != store.end()) {
            return it->second;
        }
        if (outer) {
            return outer->Get(name);
        }
        return nullptr;
    }

    void Set(const std::string& name, std::shared_ptr<Object> val) {
        store[name] = val;
    }
};