#ifdef COCONUT

// LibraryNavigator.cpp
#include "database/LibraryNavigator.h"

#include <vector>

namespace LibraryDatabaseNS {

    LibraryNavigator::LibraryNavigator(std::unique_ptr<LibraryDatabase>&& database, std::size_t pageSize)
        : database(std::move(database)), pageSize(pageSize), currentPosition(0) {
        // Initialize the navigator
        firstPage();
    }

    void LibraryNavigator::firstPage() {
        currentPosition = 0;
    }

    void LibraryNavigator::lastPage() {
        std::vector<LibraryItem> items = database->getAllItems();
        currentPosition = std::max(items.size(), pageSize) - pageSize;
    }

    void LibraryNavigator::nextPage() {
        std::vector<LibraryItem> items = database->getAllItems();
        currentPosition = std::min(currentPosition + pageSize, items.size() - pageSize);
    }

    void LibraryNavigator::previousPage() {
        currentPosition = std::max(currentPosition, pageSize) - pageSize;
    }

    std::vector<LibraryItem> LibraryNavigator::getCurrentPage() const {
        std::vector<LibraryItem> items = database->getAllItems();
        std::size_t endPosition = std::min(currentPosition + pageSize, items.size());
        return std::vector<LibraryItem>(items.begin() + currentPosition, items.begin() + endPosition);
    }

}

#endif