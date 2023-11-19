#include "LibraryManager.h"

#include <iostream>

int main(int argc, char *argv[]) {
    int status = EXIT_FAILURE;

    try {
        LibraryManager libraryManager = LibraryManager(argc, argv);

        status = EXIT_SUCCESS;
    } catch (const ManagerException &e) {
        std::cout << "[" << e.getExceptionKind() << "] " << e.what() << std::endl;
        status = e.getExceptionKind();
    } catch (...) {
        std::cout << "Unsupported error happend!" << std::endl;
    }

    return status;
}