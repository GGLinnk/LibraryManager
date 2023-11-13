#pragma once

#include "LibraryUI.h"
#include <ftxui/screen/screen.hpp>

namespace LibraryUINS {
    class FTXUILibraryUI : public LibraryUI {
    public:
        FTXUILibraryUI();

        void displayMenu() override;
    };
}