#pragma once

#include "LibraryDatabase.h"
#include "LibraryItem.h"

#include <SQLiteCpp/SQLiteCpp.h>
#include <vector>

class SQLiteLibraryDatabase : public LibraryDatabase {
public:
    explicit SQLiteLibraryDatabase(const std::filesystem::path &dbPath);

    bool initialize() override;
    bool isInitialized() const override;

    void saveItem(const LibraryItem &item) override;
    void saveKind(const ItemKind &kind) override;
    /* std::vector<LibraryItem> getAllItems() const override;
    std::vector<LibraryItem> searchItems(const std::string& searchTerm) const override;
    std::vector<LibraryItem> sortItemsByName() const override; */

private:
    bool initialized;
    SQLite::Database database;
    std::string dbtype = "SQLite3";
};
