#include "database/SQLiteLibraryDatabase.h"

#include <iostream>

const std::filesystem::path SQLiteLibraryDatabase::getLibraryDatabasePath(
    const std::filesystem::path &appDataFolder,
    const std::string &dbFileName
) {
    std::filesystem::path libraryDatabasePath(appDataFolder);

    return libraryDatabasePath.append(dbFileName);
}

SQLiteLibraryDatabase::SQLiteLibraryDatabase(const std::filesystem::path &dataFolder, const std::string &databaseFileName) :
database(getLibraryDatabasePath(dataFolder, databaseFileName), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
    try {
        database.exec("CREATE TABLE IF NOT EXISTS library_items (id INTEGER PRIMARY KEY, name TEXT, author TEXT, description TEXT, kind INTEGER)");
        database.exec("CREATE TABLE IF NOT EXISTS item_kinds (id INTEGER PRIMARY KEY, name TEXT)");
    } catch(SQLite::Exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return;
    }

    initialized = true;
}

SQLiteLibraryDatabase::SQLiteLibraryDatabase(const std::filesystem::path &dataFolder) :
SQLiteLibraryDatabase::SQLiteLibraryDatabase(dataFolder, std::string(DEFAULT_DB_FILENAME)) {}

void SQLiteLibraryDatabase::saveItem(const LibraryItem& item) {
    if (!checkItemDB(item))
        return;
    if (item.getId() <= 0) {
        SQLite::Statement query(database, "INSERT INTO library_items (name, author, description, kind) VALUES (?, ?, ?, ?)");
        query.bind(1, item.getName());
        query.bind(2, item.getAuthor());
        query.bind(3, item.getDescription());
        query.bind(4, item.getItemKind().getId());
        query.exec();
    } else {
        // Check if the item with the specified ID exists
        SQLite::Statement existsQuery(database, "SELECT COUNT(*) FROM library_items WHERE id = ?");
        existsQuery.bind(1, item.getId());

        if (existsQuery.executeStep() && existsQuery.getColumn(0).getInt() > 0) {
            // Update an existing item
            SQLite::Statement updateQuery(database, "UPDATE library_items SET name = ?, author = ?, description = ?, kind = ? WHERE id = ?");
            updateQuery.bind(1, item.getName());
            updateQuery.bind(2, item.getAuthor());
            updateQuery.bind(3, item.getDescription());
            updateQuery.bind(4, item.getItemKind().getId());
            updateQuery.bind(5, item.getId());
            updateQuery.exec();
        } else {
            // Item with the specified ID does not exist
            throw std::runtime_error("Cannot update non-existent item with ID: " + std::to_string(item.getId()));
        }
    }
}

void SQLiteLibraryDatabase::saveItemKind(const ItemKind& kind) {
    //Logger::getDatabaseLogger()->info("SQLiteLibraryDatabase saveItemKind");

    if (kind.getId() <= 0) {
        // Insert a new kind
        SQLite::Statement query(database, "INSERT INTO item_kinds (name) VALUES (?)");
        query.bind(1, kind.getName());
        query.exec();
    } else {
        // Check if the kind with the specified ID exists
        SQLite::Statement query(database, "SELECT COUNT(*) FROM item_kinds WHERE id = ?");
        query.bind(1, kind.getId());

        if (query.executeStep() && query.getColumn(0).getInt() > 0) {
            // Update an existing kind
            SQLite::Statement updateKindQuery(database, "UPDATE item_kinds SET name = ? WHERE id = ?");
            updateKindQuery.bind(1, kind.getName());
            updateKindQuery.bind(2, kind.getId());
            updateKindQuery.exec();
        } else {
            // ItemKind with the specified ID does not exist
            throw std::runtime_error("Cannot update non-existent kind with ID: " + std::to_string(kind.getId()));
        }
    }
}

bool SQLiteLibraryDatabase::checkItemDB(const LibraryItem& item) {
    if (item.getId() == 0)
        if (checkItemExists(item))
            return false;
    if (item.getId() > 0)
        if (!checkItemIdExists(item.getId()))
            return false;

    return true;
}

bool SQLiteLibraryDatabase::checkItemExists(const LibraryItem& item) {
    SQLite::Statement query(database, "SELECT 1 FROM library_items WHERE name = ? AND author = ? LIMIT 1;");

    query.bind(1, item.getName());
    query.bind(2, item.getAuthor());

    return query.executeStep();
}

bool SQLiteLibraryDatabase::checkItemIdExists(long int id) {
    SQLite::Statement query(database, "SELECT 1 FROM library_items WHERE id = :input_id LIMIT 1;");

    query.bind(1, id);

    return query.executeStep();
}

bool SQLiteLibraryDatabase::isInitialized() const {
    return initialized;
}
