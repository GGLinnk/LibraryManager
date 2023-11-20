#pragma once

#include "config.h"

#ifndef FTXUI_DISABLED

#include "LibraryUI.h"
#include "LibraryItem.h"
#include "LibraryItemCategory.h"

#include <ftxui/screen/screen.hpp>

class FTXUILibraryUI : public LibraryUI {
public:
    FTXUILibraryUI();

    void displayMenu() override;

    LibraryItem gatherMissingInfoInteractiveUI(long long id, std::string name, std::string author, std::string description, std::string CategoryIsOrString);
};

#endif