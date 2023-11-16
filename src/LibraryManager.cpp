#include "LibraryManager.h"

#include <iostream>

LibraryManager::LibraryManager(int argc, char *argv[]) : app{PROJECT_NAMEVER} {
    app.allow_windows_style_options();
    app.require_subcommand(1, 1);

    configureOptions();
    configureSubcommands();

    parse(argc, argv);
    //init();
}

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

void LibraryManager::configureOptions() {
    //app.add_option("-d,--data-folder", appDataFolder, "Overrides the app data folder path.");
    //app.add_option("-f,--database-file", databaseFilePath, "Overrides the database file path");
    app.add_flag("-n,--no-ui", ui_disabled, "Prevent UI Mode");

    //std::cout << appDataFolder << std::endl;
    // Add more options as needed
}

void LibraryManager::configureSubcommands() {
    CLI::App* addCommand = app.add_subcommand("add", "Add a library item or item kind");
    addCommand->preparse_callback([this, addCommand](size_t count) { handleAddPreParse(addCommand, count); });
    addCommand->callback([this, addCommand]() { handleItemCommand(addCommand); });

    CLI::App* removeCommand = app.add_subcommand("remove", "Remove a library item or item kind");
    removeCommand->callback([this, removeCommand]() { handleItemCommand(removeCommand); });

    CLI::App* searchCommand = app.add_subcommand("search", "Search for library items or item kinds");
    searchCommand->callback([this, searchCommand]() { handleSearchCommand(searchCommand); });

    CLI::App* updateCommand = app.add_subcommand("update", "Update a library item or item kind");
    updateCommand->preparse_callback([this, updateCommand](size_t count) { handleAddPreParse(updateCommand, count); });
    updateCommand->callback([this, updateCommand]() { handleItemCommand(updateCommand); });
}

void LibraryManager::handleCommands(CLI::App* cmd) {
    // Add more logic to handle other commands and options
}

void LibraryManager::handleAddPreParse(CLI::App* cmd, size_t _) {
    cmd->add_option("-n,--name", "Name of the item you want to add.");
    cmd->add_option("-a,--author", "Author of the item you want to add.");
    cmd->add_option("-d,--description", "Description of the item you want to add.");
    cmd->add_option("-k,--kind", "Kind of the item you want to add.");
}

void LibraryManager::handlUpdatePreParse(CLI::App* cmd, size_t _) {
    cmd->add_option("-i,--id", "ID of the item you want to update.");
    cmd->add_option("-n,--name", "Name of the item you want to update.");
    cmd->add_option("-a,--author", "Author of the item you want to update.");
    cmd->add_option("-d,--description", "Description of the item you want to update.");
    cmd->add_option("-k,--kind", "Kind of the item you want to update.");
}

void LibraryManager::handleItemCommand(CLI::App* cmd) {
    CLI::Option* idOption = cmd->get_option("--id");
    CLI::Option* nameOption = cmd->get_option("--name");
    CLI::Option* authorOption = cmd->get_option("--author");
    CLI::Option* descriptionOption = cmd->get_option("--description");
    CLI::Option* kindOption = cmd->get_option("--kind");

    long int id = idOption ? idOption->as<long int>() : 0;
    std::string name = nameOption ? nameOption->as<std::string>() : "";
    std::string author = authorOption ? authorOption->as<std::string>() : "";
    std::string description = descriptionOption ? descriptionOption->as<std::string>() : "";
    std::string kindIdOrString = kindOption ? kindOption->as<std::string>() : "";

    if (ui_disabled)
        item = LibraryManager::gatherMissingInfoInteractive(id, name, author, description, kindIdOrString);
    #ifndef UI_DISABLED
    else
        item = libraryUI->gatherMissingInfoInteractiveUI(id, name, author, description, kindIdOrString);
    #endif

    if (!libraryDatabase->checkItemDB(item)) {
        throw std::runtime_error("Can't update database, item is invalid !");
    }
}

LibraryItem LibraryManager::gatherMissingInfoInteractive(long int id, std::string name, std::string author, std::string description, std::string kindIdOrString) {
    ItemKind itemKind;

    if (name.empty()) {
        std::cout << "Enter item name: ";
        std::getline(std::cin, name);
    }

    if (author.empty()) {
        std::cout << "Enter author: ";
        std::getline(std::cin, author);
    }

    if (description.empty()) {
        std::cout << "Enter description: ";
        std::getline(std::cin, description);
    }

    if (kindIdOrString.empty()) {
        std::cout << "Enter kind: ";
        std::getline(std::cin, kindIdOrString);

        try {
            int intValue = std::stoi(kindIdOrString);
            itemKind = ItemKind(intValue);
        } catch (std::invalid_argument&) {
            itemKind = ItemKind(kindIdOrString);
        }
    }

    return LibraryItem(id, name, author, description, itemKind);
}

void LibraryManager::handleSearchCommand(CLI::App* cmd) {
    // Implement logic for searching library items or item kinds
}

int LibraryManager::parse(int argc, char *argv[]) {
    CLI11_PARSE(app, argc, argv);

    arguments_parsed = true;

    return EXIT_SUCCESS;
}

void LibraryManager::init() {
    if (!arguments_parsed) {
        throw std::runtime_error("You need to parse arguments first.");
    }

    libraryDatabase = std::make_unique<SQLiteLibraryDatabase>(appDataFolder);
    libraryUI = std::make_unique<FTXUILibraryUI>();

    if (!libraryDatabase->isInitialized()) {
        throw std::runtime_error("Database is not initialized !");
    }

    initialized = true;
}
