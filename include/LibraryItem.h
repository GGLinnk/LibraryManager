#pragma once

#include "LibraryItemKind.h"

#include <string>

class LibraryItem  {
private:
    long int id;
    std::string name;
    std::string author;
    std::string description;
    ItemKind itemKind;

    bool initialized;

public:
    LibraryItem();
    LibraryItem(long int id, const std::string& name, const std::string& author, const std::string& description, const ItemKind itemKind);

    void setInitialized();
    bool isInitialized() const;

    // Getters
    long int getId() const;
    const std::string& getName() const;
    const std::string& getAuthor() const;
    const std::string& getDescription() const;
    ItemKind getItemKind() const;
};