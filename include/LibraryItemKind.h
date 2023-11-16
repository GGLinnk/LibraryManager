#pragma once

#include <string>

class ItemKind {
private:
    long int id;
    std::string name;

    bool initialized = false;
    bool empty = false;

public:
    ItemKind();
    ItemKind(long int id);
    ItemKind(const std::string &name);
    ItemKind(long int id, const std::string &name);

    bool setInitialized();
    bool isInitialized() const;
    bool isEmpty() const;

    long int getId() const;
    const std::string& getName() const;
};