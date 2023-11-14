#pragma once

#include "LibraryItem.h"
#include "LibraryItemKind.h"

#include <vector>

class LibraryDatabase {
public:
    virtual ~LibraryDatabase() = default;
    
    virtual bool isInitialized() const = 0; // New function to check initialization status

    virtual void saveItem(const LibraryItem &item) = 0;
    virtual void saveKind(const ItemKind &kind) = 0;
    /* virtual std::vector<LibraryItem> getAllItems() const = 0;
    virtual std::vector<LibraryItem> searchItems(const std::string& searchTerm) const = 0;
    virtual std::vector<LibraryItem> sortItemsByName() const = 0; */
};