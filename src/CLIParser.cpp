#include "config.h"
#include "CLIParser.h"

#include <iostream>

CLIParser::CLIParser(LibraryManager &manager) : libraryManager(manager), cliargsparser{PROJECT_NV} {
    //CLI::App* guimode = cliargsparser.add_subcommand("gui", "Graphical User Interface mode.");
    //CLI::App* tuimode = cliargsparser.add_subcommand("tui", "Terminal User Interface mode.");
    //CLI::App* appsetting = cliargsparser.add_subcommand("config", "App settings.");

    CLI::App* cliaddingmode = cliargsparser.add_subcommand("add",    "Add new items to the library.");
    CLI::App* cliremovemode = cliargsparser.add_subcommand("remove", "Remove items from the library.");
    CLI::App* clisearchmode = cliargsparser.add_subcommand("search", "Search items from the library.");

    cliargsparser.require_subcommand(1, 1);
}

int CLIParser::parse(int argc, char* argv[]) {
    CLI11_PARSE(cliargsparser, argc, argv);

    return 0;
/*
    // Handle other commands based on flags
    if (cmdl[{"tui"}]) {
        tuiMode();
    } else if (cmdl[{"gui"}]) {
        guiMode();
    } else if (cmdl[{"-a", "--add"}]) {
        std::string name, author, description, kind;

        cmdl({"-n", "--name"}) >> name;
        cmdl({"-a", "--author"}) >> author;
        cmdl({"-d", "--description"}) >> description;
        cmdl({"-k", "--kind"}) >> kind;

        libraryManager.addItem(name, author, description, kind);

        return;
    } else if (cmdl[{"-r", "--remove"}]) {
        int itemId = 0;

        cmdl({"-r", "--remove"}) >> itemId;

        libraryManager.removeItem(itemId);

        return;
    } else if (cmdl[{"-s", "--search"}]) {
        std::string search, name, author, description, kind;

        cmdl({"-s", "--search"}) >> search;
        cmdl({"-n", "--name"}) >> name;
        cmdl({"-a", "--author"}) >> author;
        cmdl({"-d", "--description"}) >> description;
        cmdl({"-k", "--kind"}) >> kind;

        std::cout << "what" << search << name << author << description << kind << std::endl;

        libraryManager.searchItems(search, name, author, description, kind);

        return;
    } else {
        std::cerr << "Error: Unrecognized command. Use '--help' for usage information.\n";

        return;
    }

    */
}