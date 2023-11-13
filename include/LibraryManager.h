#pragma once

#include <string>
#include "database/LibraryDatabase.h"
#include "ui/LibraryUI.h"
#include "LibraryItem.h"

class LibraryManager {
private:
    LibraryDatabase& libraryDatabase;
    LibraryUI& libraryUI;

public:
    LibraryManager();
    LibraryManager(LibraryDatabase &db, LibraryUI &ui);

    void displayMenu();

    //~LibraryManager();
};