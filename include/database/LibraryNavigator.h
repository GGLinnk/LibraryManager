#pragma once

#ifdef COCONUT

#include "LibraryDatabase.h"

#include <memory>
#include <vector>

class LibraryNavigator {
public:
    explicit LibraryNavigator(std::unique_ptr<LibraryDatabase>&& database, std::size_t pageSize);

    void firstPage();
    void lastPage();
    void nextPage();
    void previousPage();
    std::vector<LibraryItem> getCurrentPage() const;

private:
    std::unique_ptr<LibraryDatabase> database;
    std::size_t pageSize;
    std::size_t currentPosition;
};

#endif
