#pragma once

#include "LibraryUI.h"
#include "LibraryItem.h"
#include "LibraryItemKind.h"

#include <ftxui/screen/screen.hpp>

class FTXUILibraryUI : public LibraryUI {
public:
    FTXUILibraryUI();

    void displayMenu() override;

    LibraryItem gatherMissingInfoInteractiveUI(long int id, std::string name, std::string author, std::string description, std::string kindIsOrString);
};