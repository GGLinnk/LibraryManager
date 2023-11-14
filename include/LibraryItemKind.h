#pragma once

#include <string>

class ItemKind {
public:
    explicit ItemKind(long int id, const std::string &name);
    explicit ItemKind(const std::string &name);
    explicit ItemKind(long int id);
    explicit ItemKind();

    const long int getId() const;
    const std::string& getName() const;

private:
    long int id;
    std::string name;
    bool initialized = false;
};