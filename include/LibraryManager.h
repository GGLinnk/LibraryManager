#pragma once

#define APP_NAME "LibraryManager"

#include "LibraryItem.h"

#include "database/LibraryDatabase.h"
#include "database/SQLiteLibraryDatabase.h"

#include "ui/LibraryUI.h"
#include "ui/FTXUILibraryUI.h"

#include <string>
#include <filesystem>

class LibraryManager {
private:
    LibraryDatabase &&libraryDatabase;
    LibraryUI &&libraryUI;
    const std::filesystem::path &appDataFolder;

    const std::filesystem::path getAppDataFolder(const std::string &appName);

    bool isValidItemId(int itemId);

public:
    explicit LibraryManager(const std::filesystem::path &appDataFolder);
    explicit LibraryManager();

    void addItem(
        const long int id,
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