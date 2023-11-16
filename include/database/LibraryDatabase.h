#pragma once

#include "LibraryItem.h"
#include "LibraryItemKind.h"
#include "LibraryExceptions.h"

#include <vector>

class LibraryDatabase {
public:
    virtual ~LibraryDatabase() = default;
    
    virtual bool isInitialized() const = 0; // New function to check initialization status

    virtual bool checkItemDB(const LibraryItem &item) = 0;
    virtual void saveItem(const LibraryItem &item) = 0;
    virtual void saveItemKind(const ItemKind &kind) = 0;
    /* virtual std::vector<LibraryItem> getAllItems() const = 0;
    virtual std::vector<LibraryItem> searchItems(const std::string& searchTerm) const = 0;
    virtual std::vector<LibraryItem> sortItemsByName() const = 0; */
};