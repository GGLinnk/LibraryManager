#pragma once

#include <string>

class ItemKind {
private:
    long long id;
    std::string name;

    bool initialized = false;
    bool empty = true;

public:
    ItemKind();
    ItemKind(long long id);
    ItemKind(const std::string& name);
    ItemKind(long long id, const std::string& name);

    bool setInitialized();
    bool isInitialized() const;
    bool isEmpty() const;

    long long getId() const;
    const std::string& getName() const;
};