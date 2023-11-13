#include "LibraryManager.h"

#include "database/SQLiteLibraryDatabase.h"
#include "ui/FTXUILibraryUI.h"

#include <iostream>

int main(int ac, char **av, char **env) {
    std::cout << "Starting LibraryManager..." << std::endl;

    SQLiteLibraryDatabase sqliteDatabase("library.db");
    FTXUILibraryUI ftxuiUI;

    // Check if the database is initialized
    if (!sqliteDatabase.isInitialized()) {
        std::cerr << "Error: Database initialization failed." << std::endl;
        return 1;
    }

    LibraryManager libraryManager(sqliteDatabase, ftxuiUI);
    libraryManager.displayMenu();

    std::cout << "LibraryManager finished." << std::endl;

    return EXIT_SUCCESS;
}