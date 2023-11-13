#pragma once

#include <string>

class ItemKind {
public:
    ItemKind(long int id, const std::string &name);

    long int getId() const;
    const std::string& getName() const;

private:
    long int id;
    std::string name;
};