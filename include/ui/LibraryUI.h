#pragma once

class LibraryUI {
public:
    virtual ~LibraryUI() = default;

    virtual void displayMenu() = 0;
};