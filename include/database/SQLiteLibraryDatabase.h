#pragma once

#define DEFAULT_DB_FILENAME "library.db"

#include "LibraryDatabase.h"
#include "LibraryItem.h"

#include <SQLiteCpp/SQLiteCpp.h>
#include <vector>

class SQLiteLibraryDatabase : public LibraryDatabase {
public:
    explicit SQLiteLibraryDatabase(const std::filesystem::path &dataFolder, const std::string &databaseFileName);
    explicit SQLiteLibraryDatabase(const std::filesystem::path &dataFolder);

    const std::filesystem::path getLibraryDatabasePath(const std::filesystem::path &appDataFolder, const std::string &dbFileName);

    bool isInitialized() const override;

    void saveItem(const LibraryItem &item) override;
    void saveKind(const ItemKind &kind) override;
    /* std::vector<LibraryItem> getAllItems() override;
    std::vector<LibraryItem> searchItems(const std::string& searchTerm) override;
    std::vector<LibraryItem> sortItemsByName() override; */

private:
    SQLite::Database database;
    bool initialized = false;
};
