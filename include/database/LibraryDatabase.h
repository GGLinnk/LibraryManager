#pragma once

#include "LibraryItem.h"

#include <vector>

namespace LibraryDatabaseNS {
    class LibraryDatabase {
    public:
        virtual ~LibraryDatabase() = default;
        
        virtual bool initialize() = 0;
        virtual bool isInitialized() const = 0; // New function to check initialization status

        virtual bool saveItem(const LibraryItem& item) = 0;
        /* virtual std::vector<LibraryItem> getAllItems() const = 0;
        virtual std::vector<LibraryItem> searchItems(const std::string& searchTerm) const = 0;
        virtual std::vector<LibraryItem> sortItemsByName() const = 0; */
    };
}