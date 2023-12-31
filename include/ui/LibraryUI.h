#pragma once

#include "LibraryItem.h"
#include "LibraryItemCategory.h"

#include <string>

class LibraryUI {
public:
    virtual ~LibraryUI() = default;

    virtual void displayMenu() = 0;

    virtual LibraryItem gatherMissingInfoInteractiveUI(long long id, std::string name, std::string author, std::string description, std::string CategoryIsOrString) = 0;
};