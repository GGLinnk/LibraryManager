#include "database/SQLiteLibraryDatabase.h"

#include <iostream>

SQLiteLibraryDatabase::SQLiteLibraryDatabase(
    const std::filesystem::path& dataFolder,
    const std::string& databaseFilename)
: database(getLibraryDatabasePath(dataFolder, databaseFilename), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE)
{
    try {
        SQLite::Statement createLibraryItemsQuery(database, "CREATE TABLE IF NOT EXISTS :tableName (id INTEGER PRIMARY KEY, name TEXT, author TEXT, description TEXT, kind INTEGER)");
        SQLite::Statement createItemKindsQuery(database, "CREATE TABLE IF NOT EXISTS :tableName (id INTEGER PRIMARY KEY, name TEXT)");
        createLibraryItemsQuery.bind(":tableName", LIBRARY_ITEMS_TABLE_NAME);
        createItemKindsQuery.bind(":tableName", ITEMSKIND_TABLE_NAME);
        createLibraryItemsQuery.exec();
        createItemKindsQuery.exec();
    } catch(SQLite::Exception& e) {
        throw ManagerException(ManagerExceptionKind::DBInitFail);
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
    
    SQLite::Statement itemQuery = fetchTableRow(libraryItem.getId(), ITEMSKIND_TABLE_NAME);

    std::string name = itemQuery.getColumn("name").getText();
    std::string author = itemQuery.getColumn("author").getText();
    std::string description = itemQuery.getColumn("description").getText();
    ItemKind itemKind = itemQuery.getColumn("kind").getInt64();

    return LibraryItem(libraryItem.getId(), name, author, description, itemKind);
}

ItemKind SQLiteLibraryDatabase::fetchFullItemKind(const ItemKind& itemKind) {
    if (itemKind.getId() == 0 && itemKind.getName().empty())
        throw ManagerException(ManagerExceptionKind::InvalidItemKind, "- Item kind cannot be empty or have 0 or negative id!");

    SQLite::Statement itemKindQuery = (itemKind.getId()) ?
        fetchTableRow(itemKind.getName(), ITEMSKIND_TABLE_NAME) :
        fetchTableRow(itemKind.getId(), ITEMSKIND_TABLE_NAME);

    if (itemKindQuery.executeStep())
        throw ManagerException(ManagerExceptionKind::LibraryItemKindNotFound);

    long int id = itemKindQuery.getColumn("id").getInt64();
    std::string name = itemKindQuery.getColumn("name").getText();

    return ItemKind(id, name);
}

bool SQLiteLibraryDatabase::saveItem(const LibraryItem& item) {
    if (!checkItem(item))
        return false;

    if (item.getId() <= 0) {
        SQLite::Statement query(database, "INSERT INTO library_items (name, author, description, kind) VALUES (?, ?, ?, ?)");
        query.bind(1, item.getName());
        query.bind(2, item.getAuthor());
        query.bind(3, item.getDescription());
        query.bind(4, item.getItemKind().getId());
        query.exec();
    } else {
        SQLite::Statement existsQuery(database, "SELECT 1 FROM library_items WHERE id = ?");
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
            throw ManagerException(ManagerExceptionKind::DBEntryNotFound, std::string("- Library item ID: ").append(std::to_string(item.getId())));
        }
    }

    return true;
}

bool SQLiteLibraryDatabase::saveItem(const ItemKind& itemKind) {
    if (!checkItem(itemKind))
        return false;

    if (itemKind.getId() <= 0) {
        SQLite::Statement query(database, "INSERT INTO item_kinds (name) VALUES (?)");
        query.bind(1, itemKind.getName());
        query.exec();
    } else {
        SQLite::Statement query(database, "SELECT 1 FROM item_kinds WHERE id = ?");
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
    return removeTableRow(item.getId(), LIBRARY_ITEMS_TABLE_NAME);
}

bool SQLiteLibraryDatabase::removeItem(const ItemKind& itemKind) {
    return removeTableRow(itemKind.getId(), ITEMSKIND_TABLE_NAME);
}

bool SQLiteLibraryDatabase::checkItem(const ItemKind& itemKind) {
    if (itemKind.getId() == 0)
        if (checkItemAlreadyExists(itemKind))
            return false;
    if (itemKind.getId() > 0)
        if (!checkIdAlreadyExists(itemKind.getId(), ITEMSKIND_TABLE_NAME))
            return false;

    return true;
}

bool SQLiteLibraryDatabase::checkItem(const LibraryItem& item) {
    if (!checkItem(item.getItemKind()))
        return false;

    if (item.getId() == 0)
        if (checkItemAlreadyExists(item))
            return false;
    if (item.getId() > 0)
        if (!checkIdAlreadyExists(item.getId(), LIBRARY_ITEMS_TABLE_NAME))
            return false;

    return true;
}

SQLite::Statement SQLiteLibraryDatabase::fetchTableRowById(const long int id, const std::string& tableName) {
    SQLite::Statement fetchQuery(database, "SELECT 1 FROM :tableName WHERE id = :id LIMIT 1;");

    fetchQuery.bind(":tableName", tableName);
    fetchQuery.bind(":id", id);

    return fetchQuery;
}

SQLite::Statement SQLiteLibraryDatabase::fetchTableRowByName(const std::string& name, const std::string& tableName) {
    SQLite::Statement fetchQuery(database, "SELECT 1 FROM :tableName WHERE name = :name LIMIT 1;");

    fetchQuery.bind(":tableName", tableName);
    fetchQuery.bind(":name", name);

    return fetchQuery;
}

bool SQLiteLibraryDatabase::checkItemAlreadyExists(const LibraryItem& item) {
    SQLite::Statement query(database, "SELECT 1 FROM library_items WHERE name = ? AND author = ? LIMIT 1;");

    query.bind(1, item.getName());
    query.bind(2, item.getAuthor());

    return query.executeStep();
}

bool SQLiteLibraryDatabase::checkItemAlreadyExists(const ItemKind& item) {
    SQLite::Statement query(database, "SELECT 1 FROM item_kinds WHERE name = ? AND author = ? LIMIT 1;");

    query.bind(1, item.getName());

    return query.executeStep();
}

bool SQLiteLibraryDatabase::checkIdAlreadyExists(const long int id, const std::string& tableName) {
    SQLite::Statement query(database, "SELECT 1 FROM :tableName WHERE id = :lookId LIMIT 1;");

    query.bind(":tableName", tableName);
    query.bind(":LookId", id);

    return query.executeStep();
}

bool SQLiteLibraryDatabase::removeTableRow(const long int itemId, const std::string& tableName) {
    SQLite::Statement query(database, "DELETE FROM ? WHERE id = ?");
    
    query.bind(1, tableName);
    query.bind(2, itemId);

    return query.exec() > 0;
}