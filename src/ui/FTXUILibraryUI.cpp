#include "ui/FTXUILibraryUI.h"

FTXUILibraryUI::FTXUILibraryUI() {

}

void FTXUILibraryUI::displayMenu() {
    
}

LibraryItem FTXUILibraryUI::gatherMissingInfoInteractiveUI(long long id, std::string name, std::string author, std::string description, std::string kindIdOrString) {
    ItemKind itemKind;
/*     input_name = ftxui::Input(name, "Enter item name: ");
    input_author = ftxui::Input(author, "Enter author: ");
    input_description = ftxui::Input(description, "Enter description: ");
    input_kind = ftxui::Input(kindIdOrString, "Enter kind ID: ");
    interaction_mode = ftxui::Container::Horizontal({
        ftxui::Button("Save", [&] { handleAddInteraction(); }),
        ftxui::Button("Cancel", [&] { /* handle cancel logic }),
    }); */

    return LibraryItem(id, name, author, description, itemKind);
}