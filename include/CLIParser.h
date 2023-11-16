#ifdef DEAD_CODE
#pragma once

#include "config.h"

#include "LibraryItem.h"

#include <CLI/CLI.hpp>

class CLIParser {
public:
    explicit CLIParser();

    int parse(int argc, char* argv[]);

private:
    CLI::App app;

    void configureOptions();
    void configureSubcommands();

    void handleCommands();
    void handleAddCommand();
    void handleRemoveCommand();
    void handleSearchCommand();
    void handleUpdateCommand();
};
#endif