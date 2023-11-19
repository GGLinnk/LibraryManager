#pragma once

#include "config.h"

#define DEFAULT_DB_FILENAME PROJECT_NAME ".db"

#include "LibraryDatabase.h"
#include "LibraryItem.h"

#include <SQLiteCpp/SQLiteCpp.h>
#include <vector>

class SQLiteLibraryDatabase : public LibraryDatabase {
public:
    SQLiteLibraryDatabase(const std::filesystem::path& dataFolder, const std::string& databaseFilename);

    const std::filesystem::path getLibraryDatabasePath(const std::filesystem::path& appDataFolder, const std::string& dbFileName);

    LibraryItem fetchFullItem(const LibraryItem& libraryItem) override;
    ItemKind fetchFullItemKind(const ItemKind& itemKind) override;

    bool checkItem(const LibraryItem& libraryItem) override;
    bool checkItem(const ItemKind& itemKind) override;

    bool saveItem(const LibraryItem& libraryItem) override;
    bool saveItem(const ItemKind& itemKind) override;

    bool removeItem(const LibraryItem& libraryItem) override;
    bool removeItem(const ItemKind& itemKind) override;

private:
    //std::unique_ptr<SQLite::Database> database;
    SQLite::Database database;

    SQLite::Statement fetchTableRowById(const long int id, const std::string& tableName);
    SQLite::Statement fetchTableRowByName(const std::string& name, const std::string& tableName); 

    bool checkItemAlreadyExists(const LibraryItem& item);
    bool checkItemAlreadyExists(const ItemKind& itemKind);
    
    bool checkIdAlreadyExists(const long int id, const std::string& tableName);

    bool removeTableRow(const long int id, const std::string& tableName);
};
