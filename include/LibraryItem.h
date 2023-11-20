#pragma once

#include "LibraryItemKind.h"

#include <string>

class LibraryItem  {
private:
    long long id;
    std::string name;
    std::string author;
    std::string description;
    ItemKind itemKind;

    bool empty = true;
    bool initialized = false;

public:
    LibraryItem();
    LibraryItem(long long id);
    LibraryItem(const std::string& name, const std::string& author, const std::string& description, const ItemKind itemKind);
    LibraryItem(long long id, const std::string& name, const std::string& author, const std::string& description, const ItemKind itemKind);

    void setInitialized();
    bool isInitialized() const;
    bool isEmpty() const;

    // Getters
    long long getId() const;
    const std::string& getName() const;
    const std::string& getAuthor() const;
    const std::string& getDescription() const;
    ItemKind getItemKind() const;
};