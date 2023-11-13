#pragma once

#include <string>
#include "database/LibraryDatabase.h"
#include "ui/LibraryUI.h"
#include "LibraryItem.h"

namespace LibraryManagerNS {
    class LibraryManager {
    private:
        LibraryDatabaseNS::LibraryDatabase& libraryDatabase;
        LibraryUINS::LibraryUI& libraryUI;

    public:
        LibraryManager();
        LibraryManager(LibraryDatabaseNS::LibraryDatabase &db, LibraryUINS::LibraryUI &ui);

        void initializeDatabase();
        void displayMenu();

        //~LibraryManager();
    };
}