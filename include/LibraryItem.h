#pragma once

#include "LibraryItemKind.h"

#include <string>

class LibraryItem  {
private:
    ItemKind kind;
    long int id;
    std::string name;
    std::string author;
    std::string description;

public:
    explicit LibraryItem(int id, const std::string &name, const std::string &author, const std::string &description, const ItemKind kind);

    // Getters
    int getId() const;
    const std::string &getName() const;
    const std::string &getAuthor() const;
    const std::string &getDescription() const;
    ItemKind getKind() const;

    bool set_kind();
};