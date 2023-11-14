#pragma once

#include "LibraryManager.h"
#include <CLI/CLI.hpp>

class CLIParser {
public:
    explicit CLIParser(LibraryManager& manager);

    int parse(int argc, char* argv[]);

private:
    LibraryManager& libraryManager;
    CLI::App cliargsparser;
};