#pragma once

#include "config.h"

#define DEFAULT_DB_FILENAME PROJECT_NAME ".db"

#include "LibraryDatabase.h"
#include "LibraryItem.h"

#include <SQLiteCpp/SQLiteCpp.h>

#include <vector>
#include <filesystem>

class SQLiteLibraryDatabase : public LibraryDatabase {
public:
    SQLiteLibraryDatabase(const std::filesystem::path& dataFolder, const std::string& databaseFilename);

    const std::filesystem::path getLibraryDatabasePath(const std::filesystem::path& appDataFolder, const std::string& dbFileName);

    LibraryItem fetchFullItem(const LibraryItem& libraryItem) override;
    LibraryItemCategory fetchFullItemCategory(const LibraryItemCategory& libraryItemCategory) override;

    bool checkItem(const LibraryItem& libraryItem) override;
    bool checkItemCategory(const LibraryItemCategory& libraryItemCategory) override;

    bool saveItem(const LibraryItem& libraryItem) override;
    bool saveItemCategory(const LibraryItemCategory& libraryItemCategory) override;

    bool removeItem(const LibraryItem& libraryItem) override;
    bool removeItemCategory(const LibraryItemCategory& libraryItemCategory) override;

    std::vector<LibraryItem> searchItemsByName(const std::string& name) override;
    std::vector<LibraryItem> searchItemsByAuthor(const std::string& author) override;
    std::vector<LibraryItem> searchItemsByKeywords(const std::vector<std::string>& keywords) override;

    std::vector<LibraryItemCategory> searchCategoriesByName(const std::string& name) override;

private:
    //std::unique_ptr<SQLite::Database> database;
    SQLite::Database database;

    SQLite::Statement fetchTableRowById(const long long id, const std::string& tableName);
    SQLite::Statement fetchTableRowByName(const std::string& name, const std::string& tableName); 

    bool checkItemAlreadyExists(const LibraryItem& item);
    bool checkItemCategoryAlreadyExists(const LibraryItemCategory& libraryItemCategory);
    bool checkIdExists(const long long id, const std::string& tableName);

    bool removeTableRowById(const long long id, const std::string& tableName);
};
