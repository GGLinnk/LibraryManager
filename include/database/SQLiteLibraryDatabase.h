#pragma once

#include "LibraryDatabase.h"
#include "LibraryItem.h"

#include <SQLiteCpp/SQLiteCpp.h>
#include <vector>

namespace LibraryDatabaseNS {

    class SQLiteLibraryDatabase : LibraryDatabase {
    public:
        SQLiteLibraryDatabase(const std::string& dbName);

        bool initialize();
        bool isInitialized() const override;

        bool saveItem(const LibraryItem& item) override;
        /* std::vector<LibraryItem> getAllItems() const override;
        std::vector<LibraryItem> searchItems(const std::string& searchTerm) const override;
        std::vector<LibraryItem> sortItemsByName() const override; */

    private:
        bool initialized;
        SQLite::Database database;
    };

}