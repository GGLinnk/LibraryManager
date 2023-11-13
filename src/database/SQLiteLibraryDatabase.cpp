#include "database/SQLiteLibraryDatabase.h"

#include <iostream>

namespace LibraryDatabaseNS {

    SQLiteLibraryDatabase::SQLiteLibraryDatabase(const std::string& dbName) : database(dbName, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE), initialized(false) {
        initialized = initialize();
    }

    bool SQLiteLibraryDatabase::initialize() {
        try {
            database.exec("CREATE TABLE IF NOT EXISTS library_items (id INTEGER PRIMARY KEY, name TEXT, author TEXT, description TEXT, kind INTEGER)");
        } catch(SQLite::Exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return false;
        }

        return true;
    }

    bool SQLiteLibraryDatabase::saveItem(const LibraryItem& item) {
        SQLite::Statement query(database, "INSERT INTO library_items (name, author, description, kind) VALUES (?, ?, ?, ?)");
        query.bind(1, item.getName());
        query.bind(2, item.getAuthor());
        query.bind(3, item.getDescription());
        query.bind(4, static_cast<int>(item.getKind()));

        try {
            query.exec();
        } catch(SQLite::Exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return false;
        }

        return true;
    }

    bool SQLiteLibraryDatabase::isInitialized() const {
        return initialized;
    }

}