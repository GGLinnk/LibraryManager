#pragma once

#include "config.h"

#include "LibraryItem.h"
#include "LibraryItemKind.h"

#include "database/LibraryDatabase.h"
#include "ui/LibraryUI.h"

#include "database/SQLiteLibraryDatabase.h"
#include "ui/FTXUILibraryUI.h"

#include <CLI/CLI.hpp>

#include <string>
#include <filesystem>

class LibraryManager {
private:
    CLI::App app;
    LibraryItem item;

    std::unique_ptr<LibraryDatabase> libraryDatabase;
    std::unique_ptr<LibraryUI> libraryUI;
    //LibraryUI* libraryUI = new FTXUILibraryUI();

    bool arguments_parsed = false;
    bool initialized = false;
    bool interactive = false;
    bool ui_disabled = UI_DISABLED;

    std::filesystem::path appDataFolder;
    std::filesystem::path databaseFilePath;

    const std::filesystem::path getAppDataFolder(const std::string &appName);

    void configureOptions();
    void configureSubcommands();

    void handleCommands(CLI::App* cmd);
    
    void handleItemCommand(CLI::App* cmd);
    void handleSearchCommand(CLI::App* cmd);

    void handleAddPreParse(CLI::App* cmd, size_t count);
    void handlUpdatePreParse(CLI::App* cmd, size_t count);
    
    LibraryItem gatherMissingInfoInteractive(long int id, std::string name, std::string author, std::string description, std::string kindIdOrrString);

    int parse(int argc, char *argv[]);
    void init();
    
public:
    LibraryManager(int argc, char *argv[]);

};