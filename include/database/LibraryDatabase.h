#pragma once

#define LIBRARY_ITEMS_TABLE_NAME "library_items"
#define ITEM_CATEGORIES_TABLE_NAME "item_categories"

#include "LibraryItem.h"
#include "LibraryItemCategory.h"
#include "LibraryExceptions.h"

#include <vector>

class LibraryDatabase {
public:
    virtual ~LibraryDatabase() = default;

    virtual LibraryItem fetchFullItem(const LibraryItem& libraryItem) = 0;
    virtual LibraryItemCategory fetchFullItemCategory(const LibraryItemCategory& libraryItemCategory) = 0;

    virtual bool checkItem(const LibraryItem& libraryItem) = 0;
    virtual bool checkItemCategory(const LibraryItemCategory& libraryItemCategory) = 0;

    virtual bool saveItem(const LibraryItem& libraryItem) = 0;
    virtual bool saveItemCategory(const LibraryItemCategory& libraryItemCategory) = 0;

    virtual bool removeItem(const LibraryItem& libraryItem) = 0;
    virtual bool removeItemCategory(const LibraryItemCategory& libraryItemCategory) = 0;

    /* virtual std::vector<LibraryItem> getAllItems() const = 0;
    virtual std::vector<LibraryItem> searchItems(const std::string& searchTerm) const = 0;
    virtual std::vector<LibraryItem> sortItemsByName() const = 0; */
};