#include "LibraryManager.h"
#include "CLIParser.h"

#include <iostream>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

int main(int argc, char **argv, char **env) {
    LibraryManager libraryManager;
    CLIParser cliParser(libraryManager);

    cliParser.parse(argc, argv);
   
    return EXIT_SUCCESS;
}