#pragma once

#define DEFAULT_DB_FILENAME "library.db"

#include "LibraryDatabase.h"
#include "LibraryItem.h"

#include <SQLiteCpp/SQLiteCpp.h>
#include <vector>

class SQLiteLibraryDatabase : public LibraryDatabase {
public:
    SQLiteLibraryDatabase(const std::filesystem::path &dataFolder, const std::string &databaseFileName);
    SQLiteLibraryDatabase(const std::filesystem::path &dataFolder);

    const std::filesystem::path getLibraryDatabasePath(const std::filesystem::path &appDataFolder, const std::string &dbFileName);

    bool isInitialized() const override;

    bool checkItemDB(const LibraryItem& item) override;
    void saveItem(const LibraryItem& item) override;
    void saveItemKind(const ItemKind& kind) override;

private:
    SQLite::Database database;
    bool initialized = false;

    bool checkItemExists(const LibraryItem& item);
    bool checkItemIdExists(long int id);
};
