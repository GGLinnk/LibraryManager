#ifdef DEAD_CODE
#include "CLIParser.h"

#include <iostream>

CLIParser::CLIParser() : app{PROJECT_NAMEVER} {
    app.allow_windows_style_options();
    app.require_subcommand(1, 1);

    configureOptions();
    configureSubcommands();
}

void CLIParser::configureOptions() {
    //app.add_option("-d,--database", libraryManager.database.databasePath, "Path to the database");
    // Add more options as needed
}

void CLIParser::configureSubcommands() {
    auto addCommand = app.add_subcommand("add", "Add a library item or item kind");
    addCommand->callback([this]() { handleAddCommand(); });

    auto removeCommand = app.add_subcommand("remove", "Remove a library item or item kind");
    removeCommand->callback([this]() { handleRemoveCommand(); });

    auto searchCommand = app.add_subcommand("search", "Search for library items or item kinds");
    searchCommand->callback([this]() { handleSearchCommand(); });

    auto updateCommand = app.add_subcommand("update", "Update a library item or item kind");
    updateCommand->callback([this]() { handleUpdateCommand(); });
}

void CLIParser::handleCommands() {
    // Add more logic to handle other commands and options
}

void CLIParser::handleAddCommand() {
    std::string name, author, description;
    int kindId;

    std::cout << "Enter item name: ";
    std::getline(std::cin, name);

    std::cout << "Enter author: ";
    std::getline(std::cin, author);

    std::cout << "Enter description: ";
    std::getline(std::cin, description);

    std::cout << "Enter kind ID: ";
    std::cin >> kindId;
}

void CLIParser::handleRemoveCommand() {
    // Implement logic for removing library items or item kinds
}

void CLIParser::handleSearchCommand() {
    // Implement logic for searching library items or item kinds
}

void CLIParser::handleUpdateCommand() {
    // Implement logic for updating library items or item kinds
}

int CLIParser::parse(int argc, char *argv[]) {
    try {
        app.parse(argc, argv);
    } catch(const CLI::ParseError &e) {
        return app.exit(e);
    }

    return 0;
}
#endif