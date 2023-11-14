#pragma once

#define APP_NAME "LibraryManager"
#define LIB_DB_FILENAME "library.db"

#include "database/SQLiteLibraryDatabase.h"
#include "database/LibraryDatabase.h"

#include "ui/FTXUILibraryUI.h"
#include "ui/LibraryUI.h"

#include <string>
#include <filesystem>

class LibraryManager {
private:
    LibraryDatabase &libraryDatabase;
    LibraryUI &libraryUI;
    const std::filesystem::path &appDataFolder;

    const std::filesystem::path getAppDataFolder(const std::string &appName);
    const std::filesystem::path getLibraryDatabasePath(const std::filesystem::path &appDataFolder, const std::string &dbFileName);

    bool isValidItemId(int itemId);

public:
    explicit LibraryManager(const std::filesystem::path &appDataFolder, LibraryDatabase &&db, LibraryUI &&ui);
    explicit LibraryManager(const std::filesystem::path &appDataFolder);
    explicit LibraryManager();

    void addItem(
        const std::string& name,
        const std::string& author,
        const std::string& description,
        const std::string& kind);
    void removeItem(int itemId);
    void searchItems(
        const std::string& search,
        const std::string& name,
        const std::string& author,
        const std::string& description,
        const std::string& kind);
};