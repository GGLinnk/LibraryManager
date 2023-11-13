#pragma once

#include "LibraryUI.h"
#include <ftxui/screen/screen.hpp>

class FTXUILibraryUI : public LibraryUI {
public:
    FTXUILibraryUI();

    void displayMenu() override;
};