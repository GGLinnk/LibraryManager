#pragma once

#include "config.h"
#include "helpers.h"

#include "LibraryItem.h"
#include "LibraryItemKind.h"

#include "database/LibraryDatabase.h"
#include "ui/LibraryUI.h"

#include "database/SQLiteLibraryDatabase.h"
#include "ui/FTXUILibraryUI.h"

#include <CLI/CLI.hpp>

#include <string>
#include <filesystem>
#include <memory>

namespace fs = std::filesystem;

enum class OperationKind {
    None,
    Add,
    Update,
    Remove,
    Search
};

class LibraryManager {
private:
    CLI::App app;
    LibraryItem libraryItem;
    ItemKind itemKind;

    OperationKind operationKind = OperationKind::None;

    std::unique_ptr<LibraryDatabase> libraryDatabase;
    std::unique_ptr<LibraryUI> libraryUI;

    bool kindMode = false;

    bool arguments_parsed = false;
    bool initialized = false;
    bool interactive = false;
    bool ui_disabled = false || UI_DISABLED;

    fs::path appDataFolder;
    std::string databaseFilename;

    void setAppDataFolder(fs::path newAppDataFolder);
    void setDatabaseFilename(std::string databaseFilename);

    void cliAppConfig();
    void configureCallbacks();
    
    void handleAppPreparse(CLI::App* cmd);
    void handleItemModePreparse(CLI::App* currentMode);
    void handleItemKindModePreparse(CLI::App* currentMode);

    void handleAddItemPreparse(CLI::App* cmd);
    void handleUpdateItemPreparse(CLI::App* cmd);
    void handleRemoveItemPreparse(CLI::App* cmd);

    void handleItemCommand(CLI::App* cmd);
    void handleItemKindCommand(CLI::App* cmd);

    void handleItemSearchCommand(CLI::App* cmd);
    void handleItemKindSearchCommand(CLI::App* cmd);

    void handleRemoveItemCommand(CLI::App* cmd);
    void handleRemoveItemKindCommand(CLI::App* cmd);
    
    LibraryItem gatherMissingItemInfoInteractive(
        long long id,
        std::string& name,
        std::string& author,
        std::string& description,
        std::string& kindIdOrrString,
        bool update
    );

    ItemKind gatherMissingItemKindInfoInteractive(
        long long id,
        std::string& name,
        bool update
    );

    int parse(int argc, char *argv[]);

    void finishInit();

    void applyDatabaseAdd();
    void applyDatabaseUpdate();
    void applyDatabaseRemove();
    void applyDatabaseChanges();

    bool promptItemDeletion();

public:
    LibraryManager(int argc, char *argv[]);
};