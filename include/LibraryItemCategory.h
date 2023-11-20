#pragma once

#include <iostream>
#include <string>

class LibraryItemCategory {
private:
    long long id;
    std::string name;

    bool initialized = false;
    bool empty = true;

public:
    LibraryItemCategory();
    LibraryItemCategory(long long id);
    LibraryItemCategory(const std::string& name);
    LibraryItemCategory(long long id, const std::string& name);

    bool setInitialized();
    bool isInitialized() const;
    bool isEmpty() const;

    long long getId() const;
    const std::string& getName() const;

    friend std::ostream& operator<<(std::ostream& os, const LibraryItemCategory& libraryCategoryItem);
};