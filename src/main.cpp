#include "LibraryManager.h"
#include "database/SQLiteLibraryDatabase.h"
#include "ui/FTXUILibraryUI.h"

#include <iostream>

using namespace std;
using namespace LibraryManagerNS;
//using namespace LibraryDatabaseNS;

int main(int ac, char **av, char **env) {
    std::cout << "Starting LibraryManager..." << std::endl;

    LibraryDatabaseNS::SQLiteLibraryDatabase sqliteDatabase("library.db");
    LibraryUINS::FTXUILibraryUI ftxuiUI;

    // Check if the database is initialized
    if (!sqliteDatabase.isInitialized()) {
        // Handle initialization failure
        std::cerr << "Error: Database initialization failed." << std::endl;
        return 1;
    }

    //LibraryManagerNS::LibraryManager libraryManager(sqliteDatabase, ftxuiUI);

    /* libraryManager.initializeDatabase();
    libraryManager.displayMenu(); */

    std::cout << "LibraryManager finished." << std::endl;

    return EXIT_SUCCESS;
}