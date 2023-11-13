#include "LibraryManager.h"
#include "database/SQLiteLibraryDatabase.h"


namespace LibraryManagerNS {
    LibraryManager::LibraryManager(LibraryDatabaseNS::LibraryDatabase& db, LibraryUINS::LibraryUI& ui)
    : libraryDatabase(db), libraryUI(ui) {

    }
}