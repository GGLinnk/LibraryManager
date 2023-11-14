#include "LibraryManager.h"

#include <iostream>

const std::filesystem::path LibraryManager::getAppDataFolder(const std::string &appName) {
#ifdef WIN32
    std::filesystem::path def_appdata(std::getenv("LOCALAPPDATA"));
#elif UNIX or __linux__
    std::filesystem::path def_appdata(std::getenv("HOME"));
#endif

    def_appdata.append(appName);
    std::filesystem::create_directories(def_appdata);

    return def_appdata;
}

LibraryManager::LibraryManager(const std::filesystem::path &appDataFolder) :
appDataFolder(appDataFolder),
libraryDatabase(SQLiteLibraryDatabase(appDataFolder)),
libraryUI(FTXUILibraryUI()) {
    if (!libraryDatabase.isInitialized()) {
        throw std::runtime_error("Database is not initialized !");
    }
}

LibraryManager::LibraryManager() :
LibraryManager(
    getAppDataFolder(std::string(APP_NAME))
) {}

bool LibraryManager::isValidItemId(int itemId) {
    // Example: Validate that itemId is a positive integer
    return itemId > 0;
}

void LibraryManager::addItem(const long int id, const std::string& name, const std::string& author, const std::string& description, const std::string& kind) {
    // Validate inputs before processing
    if (name.empty() || author.empty() || description.empty() || kind.empty()) {
        throw std::runtime_error("One of the required entry is empty !");
    }

    //Item item = Item();
}

void LibraryManager::removeItem(int itemId) {
    // Validate inputs before processing
    if (!isValidItemId(itemId)) {
        // Handle invalid input
        // Example: Print an error message or throw an exception
        return;
    }

    // Process the item removal...
}

void LibraryManager::searchItems(
        const std::string& search,
        const std::string& name,
        const std::string& author,
        const std::string& description,
        const std::string& kind
) {
    ItemKind realKind;

    if (search.empty() && name.empty() && author.empty() && description.empty() && kind.empty()) {
        throw std::runtime_error("One of the required entry is empty !");
        return;
    }

    if (!kind.empty()) {

    }
}