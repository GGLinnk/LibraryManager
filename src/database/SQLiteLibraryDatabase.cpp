#include "database/SQLiteLibraryDatabase.h"

#include <iostream>

SQLiteLibraryDatabase::SQLiteLibraryDatabase(
    const std::filesystem::path& dataFolder,
    const std::string& databaseFilename)
: database(getLibraryDatabasePath(dataFolder, databaseFilename), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
    try {
        database.exec("CREATE TABLE IF NOT EXISTS " LIBRARY_ITEMS_TABLE_NAME " (id INTEGER PRIMARY KEY, name TEXT, author TEXT, description TEXT, kind INTEGER)");
        database.exec("CREATE TABLE IF NOT EXISTS " ITEMSKIND_TABLE_NAME " (id INTEGER PRIMARY KEY, name TEXT)");
    } catch(SQLite::Exception& e) {
        throw ManagerException(ManagerExceptionKind::DBInitFail, e.what());
    }
}

const std::filesystem::path SQLiteLibraryDatabase::getLibraryDatabasePath(
    const std::filesystem::path& appDataFolder,
    const std::string& dbFileName
) {
    std::filesystem::path libraryDatabasePath(appDataFolder);
    std::string realDbFileName(dbFileName);

    if (libraryDatabasePath.empty())
        throw ManagerException(ManagerExceptionKind::DBInitFail);

    if (realDbFileName.empty())
        realDbFileName = std::string(DEFAULT_DB_FILENAME);

    libraryDatabasePath.append(realDbFileName);

    return std::filesystem::absolute(libraryDatabasePath);
}

LibraryItem SQLiteLibraryDatabase::fetchFullItem(const LibraryItem& libraryItem) {
    if (libraryItem.getId() <= 0)
        throw ManagerException(ManagerExceptionKind::InvalidItemID, "- Library item ID can't be zero or negative number!");
    
    SQLite::Statement itemQuery = fetchTableRowById(libraryItem.getId(), ITEMSKIND_TABLE_NAME);

    std::string name = itemQuery.getColumn("name").getText();
    std::string author = itemQuery.getColumn("author").getText();
    std::string description = itemQuery.getColumn("description").getText();
    ItemKind itemKind = fetchFullItemKind(itemQuery.getColumn("kind").getInt64());

    return LibraryItem(libraryItem.getId(), name, author, description, itemKind);
}

ItemKind SQLiteLibraryDatabase::fetchFullItemKind(const ItemKind& itemKind) {
    if (itemKind.getId() == 0 && itemKind.getName().empty())
        throw ManagerException(ManagerExceptionKind::InvalidItemKind, "- Empty item kind cannot be fetched!");

    if (checkItemKind(itemKind))
        return itemKind;

    SQLite::Statement itemKindQuery = (itemKind.getId() == 0) ?
        fetchTableRowByName(itemKind.getName(), ITEMSKIND_TABLE_NAME) :
        fetchTableRowById(itemKind.getId(), ITEMSKIND_TABLE_NAME);

    if (!itemKindQuery.executeStep())
        throw ManagerException(ManagerExceptionKind::LibraryItemKindNotFound);

    long long id = itemKindQuery.getColumn("id").getInt64();
    std::string name = itemKindQuery.getColumn("name").getText();

    return ItemKind(id, name);
}

bool SQLiteLibraryDatabase::saveItem(const LibraryItem& libraryItem) {
    if (!checkItem(libraryItem))
        throw ManagerException(ManagerExceptionKind::InvalidItem);

    ItemKind itemKind = fetchFullItemKind(libraryItem.getItemKind());

    if (!checkItemKind(libraryItem.getItemKind()))
        return false;

    if (libraryItem.getId() <= 0) {
        SQLite::Statement query(database, "INSERT INTO library_items (name, author, description, kind) VALUES (?, ?, ?, ?)");
        query.bind(1, libraryItem.getName());
        query.bind(2, libraryItem.getAuthor());
        query.bind(3, libraryItem.getDescription());
        query.bind(4, itemKind.getId());
        query.exec();
    } else {
        SQLite::Statement existsQuery(database, "SELECT * FROM library_items WHERE id = ?");
        existsQuery.bind(1, libraryItem.getId());

        if (existsQuery.executeStep() && existsQuery.getColumn(0).getInt() > 0) {
            // Update an existing item
            SQLite::Statement updateQuery(database, "UPDATE library_items SET name = ?, author = ?, description = ?, kind = ? WHERE id = ?");
            updateQuery.bind(1, libraryItem.getName());
            updateQuery.bind(2, libraryItem.getAuthor());
            updateQuery.bind(3, libraryItem.getDescription());
            updateQuery.bind(4, itemKind.getId());
            updateQuery.bind(5, libraryItem.getId());
            updateQuery.exec();
        } else {
            throw ManagerException(ManagerExceptionKind::DBEntryNotFound, std::string("- Library item ID: ").append(std::to_string(libraryItem.getId())));
        }
    }

    return true;
}

bool SQLiteLibraryDatabase::saveItemKind(const ItemKind& itemKind) {
    if (!checkItemKind(itemKind))
        return false;

    if (itemKind.getId() <= 0) {
        SQLite::Statement query(database, "INSERT INTO item_kinds (name) VALUES (?)");
        query.bind(1, itemKind.getName());
        query.exec();
    } else {
        SQLite::Statement query(database, "SELECT * FROM item_kinds WHERE id = ?");
        query.bind(1, itemKind.getId());

        if (query.executeStep() && query.getColumn(0).getInt() > 0) {
            // Update an existing kind
            SQLite::Statement updateKindQuery(database, "UPDATE item_kinds SET name = ? WHERE id = ?");
            updateKindQuery.bind(1, itemKind.getName());
            updateKindQuery.bind(2, itemKind.getId());
            updateKindQuery.exec();
        } else {
            throw ManagerException(ManagerExceptionKind::DBEntryNotFound, std::string("- Library item kind ID: ").append(std::to_string(itemKind.getId())));
        }
    }

    return true;
}

bool SQLiteLibraryDatabase::removeItem(const LibraryItem& item) {
    return removeTableRowById(item.getId(), LIBRARY_ITEMS_TABLE_NAME);
}

bool SQLiteLibraryDatabase::removeItemKind(const ItemKind& itemKind) {
    return removeTableRowById(itemKind.getId(), ITEMSKIND_TABLE_NAME);
}

bool SQLiteLibraryDatabase::checkItemKind(const ItemKind& itemKind) {
    if (!itemKind.isInitialized())
        return false;

    if (itemKind.getId() == 0)
        if (!checkItemKindAlreadyExists(itemKind))
            return true;

    if (itemKind.getId() > 0)
        if (checkIdExists(itemKind.getId(), ITEMSKIND_TABLE_NAME))
            return true;

    return false;
}

bool SQLiteLibraryDatabase::checkItem(const LibraryItem& libraryItem) {
    // If item have not been fully initialized or if it is empty, it fails.
    if (!libraryItem.isInitialized() || libraryItem.isEmpty())
        return false;

    // If this is a new item, check if combo name/author already exists.
    if (libraryItem.getId() == 0)
        if (!checkItemAlreadyExists(libraryItem))
            return true;

    // If this is updated item, check if id exists in table.
    if (libraryItem.getId() > 0)
        if (checkIdExists(libraryItem.getId(), LIBRARY_ITEMS_TABLE_NAME))
            return true;

    return false;
}

SQLite::Statement SQLiteLibraryDatabase::fetchTableRowById(const long long id, const std::string& tableName) {
    SQLite::Statement fetchQuery(database, "SELECT * FROM " + tableName + " WHERE id = ? LIMIT 1;");

    fetchQuery.bind(1, id);

    return fetchQuery;
}

SQLite::Statement SQLiteLibraryDatabase::fetchTableRowByName(const std::string& name, const std::string& tableName) {
    SQLite::Statement fetchQuery(database, "SELECT * FROM " + tableName + " WHERE name = ? COLLATE NOCASE LIMIT 1;");

    fetchQuery.bind(1, name);

    return fetchQuery;
}

bool SQLiteLibraryDatabase::checkItemAlreadyExists(const LibraryItem& item) {
    SQLite::Statement query(database, "SELECT * FROM " LIBRARY_ITEMS_TABLE_NAME " WHERE name = ? AND author = ? COLLATE NOCASE LIMIT 1;");

    query.bind(1, item.getName());
    query.bind(2, item.getAuthor());

    return query.executeStep();
}

bool SQLiteLibraryDatabase::checkItemKindAlreadyExists(const ItemKind& itemKind) {
    SQLite::Statement query(database, "SELECT FROM " ITEMSKIND_TABLE_NAME " WHERE name = ? COLLATE NOCASE LIMIT 1;");

    query.bind(1, itemKind.getName());

    return query.executeStep();
}

bool SQLiteLibraryDatabase::checkIdExists(const long long id, const std::string& tableName) {
    SQLite::Statement query(database, "SELECT * FROM " + tableName + " WHERE id = ? LIMIT 1;");

    query.bind(1, id);

    return query.executeStep();
}

bool SQLiteLibraryDatabase::removeTableRowById(const long long itemId, const std::string& tableName) {
    SQLite::Statement query(database, "DELETE FROM " + tableName + " WHERE id = ?");
    
    query.bind(1, itemId);

    return query.exec() > 0;
}