#pragma once

#define LIBRARY_ITEMS_TABLE_NAME "library_items"
#define ITEMSKIND_TABLE_NAME "item_kinds"

#include "LibraryItem.h"
#include "LibraryItemKind.h"
#include "LibraryExceptions.h"

#include <vector>

class LibraryDatabase {
public:
    virtual ~LibraryDatabase() = default;

    virtual LibraryItem fetchFullItem(const LibraryItem& libraryItem) = 0;
    virtual ItemKind fetchFullItemKind(const ItemKind& itemKind) = 0;

    virtual bool checkItem(const LibraryItem& libraryItem) = 0;
    virtual bool checkItemKind(const ItemKind& itemKind) = 0;

    virtual bool saveItem(const LibraryItem& libraryItem) = 0;
    virtual bool saveItemKind(const ItemKind& itemKind) = 0;

    virtual bool removeItem(const LibraryItem& libraryItem) = 0;
    virtual bool removeItemKind(const ItemKind& itemKind) = 0;

    /* virtual std::vector<LibraryItem> getAllItems() const = 0;
    virtual std::vector<LibraryItem> searchItems(const std::string& searchTerm) const = 0;
    virtual std::vector<LibraryItem> sortItemsByName() const = 0; */
};