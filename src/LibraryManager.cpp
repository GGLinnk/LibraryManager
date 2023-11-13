#include "LibraryManager.h"
#include "database/SQLiteLibraryDatabase.h"

LibraryManager::LibraryManager(LibraryDatabase &db, LibraryUI &ui)
: libraryDatabase(db), libraryUI(ui) { }

void LibraryManager::displayMenu() {}