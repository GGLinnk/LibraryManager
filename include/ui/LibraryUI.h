#pragma once

namespace LibraryUINS {
    class LibraryUI {
    public:
        virtual ~LibraryUI() = default;

        virtual void displayMenu() = 0;
    };
}