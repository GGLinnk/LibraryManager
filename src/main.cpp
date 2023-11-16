#include "LibraryManager.h"

#include <iostream>
#include <spdlog/spdlog.h>

int main(int argc, char *argv[]) {
    try {
        LibraryManager libraryManager = LibraryManager(argc, argv);
    } catch (const CLI::ParseError &e) {
        std::cout << e.what();
    } catch (...) {
        std::cerr << "Unsupported error occured !" << std::endl;
    }
   
    return EXIT_SUCCESS;
}