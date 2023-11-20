#include "LibraryManager.h"

#include <iostream>

LibraryManager::LibraryManager(int argc, char *argv[]) :
    app{PROJECT_NAMEVER},
    appDataFolder(fs::path(std::getenv(APPDATAROOT)).append(PROJECT_NAME)
) {
    try {
        cliAppConfig();
        configureCallbacks();

        if (parse(argc, argv))
            throw ManagerException(ManagerExceptionKind::CLIParseError);

        finishInit();
        applyDatabaseChanges();
        displayFoundItem();
    } catch (const CLI::ParseError& e) {
        throw ManagerException(ManagerExceptionKind::CLIParseError, e.what());
    } catch(SQLite::Exception& e) {
        throw ManagerException(ManagerExceptionKind::DBException, e.what());
    }
}

void LibraryManager::setAppDataFolder(fs::path newAppDataFolder) {
    if (newAppDataFolder.empty())
        throw ManagerException(ManagerExceptionKind::CLIEmptyString, "- Empty application data folder argument!");

    newAppDataFolder = fs::absolute(newAppDataFolder);

    if (!fs::exists(newAppDataFolder))
        if (!fs::create_directories(newAppDataFolder))
            throw ManagerException(ManagerExceptionKind::FSDirectoryNotCreated, std::string("- ").append(newAppDataFolder.string()).append("\n"));

    if (!fs::is_directory(newAppDataFolder))
        throw ManagerException(ManagerExceptionKind::FSNotADirectory, std::string("- ").append(newAppDataFolder.string()).append("\n"));

    appDataFolder = newAppDataFolder;

    std::cout << PROJECT_NAME << " app data folder sucessfully set: " << newAppDataFolder.string() << std::endl;
}

void LibraryManager::setDatabaseFilename(std::string newDatabaseFilename) {
    if (newDatabaseFilename.empty())
        throw ManagerException(ManagerExceptionKind::CLIEmptyString, "- Empty database filename!");

    databaseFilename = newDatabaseFilename;

    std::cout << PROJECT_NAME << " database filename sucessfully set: " << newDatabaseFilename << std::endl;
}

void LibraryManager::cliAppConfig() {
    app.allow_windows_style_options();
    app.require_subcommand(1, 1);
    app.ignore_case();

    app.add_option_function<fs::path>("-d,--data-folder", [this](fs::path path) { setAppDataFolder(path); }, "Overrides the app data folder path.");
    app.add_option<std::string>("-f,--database-filename", databaseFilename, "Overrides the database file name. If applicable.");
}

void LibraryManager::configureCallbacks() {
    CLI::App * itemsCommand = app.add_subcommand("item", "Manage library items");
    itemsCommand->preparse_callback([this, itemsCommand](size_t _) { handleItemModePreparse(itemsCommand); });

    CLI::App * itemCategoriesCommand = app.add_subcommand("category", "Manage library item categories");
    itemCategoriesCommand->preparse_callback([this, itemCategoriesCommand](size_t _) { handleItemCategoryModePreparse(itemCategoriesCommand); });
}

void LibraryManager::handleItemModePreparse(CLI::App* currentMode) {
    this->categoryMode = false;

    CLI::App* addCommand = currentMode->add_subcommand("add", "Add a library items");
    addCommand->preparse_callback([this, addCommand](size_t _) { handleAddItemPreparse(addCommand); });
    addCommand->callback([this, addCommand]() { handleItemCommand(addCommand); });

    CLI::App* updateCommand = currentMode->add_subcommand("update", "Update a library items");
    updateCommand->preparse_callback([this, updateCommand](size_t _) { handleUpdateItemPreparse(updateCommand); });
    updateCommand->callback([this, updateCommand]() { handleItemCommand(updateCommand); });

    CLI::App* removeCommand = currentMode->add_subcommand("remove", "Remove a library items");
    removeCommand->preparse_callback([this, removeCommand](size_t _) { handleRemoveItemPreparse(removeCommand); });
    removeCommand->callback([this, removeCommand]() { handleRemoveItemCommand(removeCommand); });

    CLI::App* searchCommand = currentMode->add_subcommand("search", "Search for library items");
    searchCommand->preparse_callback([this, searchCommand](size_t _) { handleSearchItemPreparse(searchCommand); });
    searchCommand->callback([this]() { this->operationKind = OperationKind::SearchItem; });
}

void LibraryManager::handleItemCategoryModePreparse(CLI::App* currentMode) {
    this->categoryMode = true;

    CLI::App* addCommand = currentMode->add_subcommand("add", "Add a library category");
    addCommand->preparse_callback([this, addCommand](size_t _) { handleAddItemPreparse(addCommand); });
    addCommand->callback([this, addCommand]() { handleItemCategoryCommand(addCommand); });

    CLI::App* updateCommand = currentMode->add_subcommand("update", "Update a library category");
    updateCommand->preparse_callback([this, updateCommand](size_t _) { handleUpdateItemPreparse(updateCommand); });

    CLI::App* removeCommand = currentMode->add_subcommand("remove", "Remove a library category");
    removeCommand->preparse_callback([this, removeCommand](size_t _) { handleRemoveItemPreparse(removeCommand); });

    CLI::App* searchCommand = currentMode->add_subcommand("search", "Search for library category");
    searchCommand->preparse_callback([this, searchCommand](size_t _) { handleSearchItemPreparse(searchCommand); });
    searchCommand->callback([this]() { this->operationKind = OperationKind::SeachCategory; });
}

void LibraryManager::handleAddItemPreparse(CLI::App* cmd) {
    cmd->add_option("-n,--name", "Name of the item you want to add.");

    if (categoryMode) return;

    cmd->add_option("-a,--author", "Author of the item you want to add.");
    cmd->add_option("-d,--description", "Description of the item you want to add.");
    cmd->add_option("-i,--item-category", "Category of the item you want to add.");
}

void LibraryManager::handleUpdateItemPreparse(CLI::App* cmd) {
    cmd->add_option("--id", "ID of the item you want to update.");
    cmd->add_option("-n,--name", "Name of the item you want to update.");

    if (categoryMode) return;

    cmd->add_option("-a,--author", "Author of the item you want to update.");
    cmd->add_option("-d,--description", "Description of the item you want to update.");
    cmd->add_option("-i,--item-category", "Category of the item you want to update.");
}

void LibraryManager::handleRemoveItemPreparse(CLI::App* cmd) {
    cmd->add_option("--id", "ID of the item you want to remove.");
}

void LibraryManager::handleSearchItemPreparse(CLI::App* cmd) {
    cmd->add_option("-n,--name", elemName, "Name of the item you want to add.");

    if (categoryMode) return;

    cmd->add_option("-a,--author", elemAuthor, "Author of the item you want to add.");
    cmd->add_option("-k,--keyords", searchKeywords, "Space or coma separated keywords to search. I will search in names, authors and description");
}

void LibraryManager::handleItemCommand(CLI::App* cmd) {
    CLI::Option* idOption = nullptr;

    try {
        idOption = cmd->get_option("--id");
        operationKind = OperationKind::Update;
    } catch (const CLI::OptionNotFound& e) {
        operationKind = OperationKind::Add;
    }

    long long id = idOption ? idOption->as<long long>() : 0;
    std::string name = cmd->get_option("--name")->as<std::string>();
    std::string author = cmd->get_option("--author")->as<std::string>();
    std::string description = cmd->get_option("--description")->as<std::string>();
    std::string kindIdOrString = cmd->get_option("--item-category")->as<std::string>();

    libraryItem = LibraryManager::gatherMissingItemInfoInteractive(id, name, author, description, kindIdOrString, operationKind == OperationKind::Update);
}

void LibraryManager::handleItemCategoryCommand(CLI::App* cmd) {
    CLI::Option* idOption = nullptr;

    try {
        idOption = cmd->get_option("--id");
        operationKind = OperationKind::Update;
    } catch (const CLI::OptionNotFound& e) {
        operationKind = OperationKind::Add;
    }

    long long id = idOption ? idOption->as<long long>() : 0;
    std::string name = cmd->get_option("--name")->as<std::string>();

    libraryItemCategory = LibraryManager::gatherMissingItemCategoryInfoInteractive(id, name, operationKind == OperationKind::Update);
}

void LibraryManager::handleRemoveItemCommand(CLI::App* cmd) {
    long long id = cmd->get_option("--id")->as<long long>();

    operationKind = OperationKind::Remove;

    if (id > 0)
        libraryItem = LibraryItem(id);
    else if (id <= 0)
        throw ManagerException(ManagerExceptionKind::InvalidUpdateID, "- Can't edit ID less or equal than 0!");
}

void LibraryManager::handleRemoveItemCategoryCommand(CLI::App* cmd) {
    long long id = cmd->get_option("--id")->as<long long>();

    operationKind = OperationKind::Remove;

    if (id > 0)
        libraryItemCategory = LibraryItemCategory(id);
    else if (id <= 0)
        throw ManagerException(ManagerExceptionKind::InvalidUpdateID, "- Can't edit ID less or equal than 0!");
}

LibraryItem LibraryManager::gatherMissingItemInfoInteractive(
    long long id,
    std::string& name,
    std::string& author,
    std::string& description,
    std::string& kindIdOrString,
    bool update
) {
    if (update && !promptUserLL(id, "id"))
        throw ManagerException(ManagerExceptionKind::InvalidUpdateID);

    if (!promptUserString(name, "name", update ? 0 : 3) && !update)
        throw ManagerException(ManagerExceptionKind::EmptyAddItem);
    if (!promptUserString(author, "author", update ? 0 : 3) && !update)
        throw ManagerException(ManagerExceptionKind::EmptyAddItem);
    if (!promptUserString(description, "description", update ? 0 : 3) && !update)
        throw ManagerException(ManagerExceptionKind::EmptyAddItem);
    if (!promptUserString(kindIdOrString, "category", update ? 0 : 3) && !update)
        throw ManagerException(ManagerExceptionKind::EmptyAddItem);

    if (update && name.empty() && author.empty() && description.empty() && kindIdOrString.empty())
        throw ManagerException(ManagerExceptionKind::EmptyUpdatePrompt);

    return LibraryItem(id, name, author, description, LibraryItemCategory(kindIdOrString));
}

LibraryItemCategory LibraryManager::gatherMissingItemCategoryInfoInteractive(
    long long id,
    std::string& name,
    bool update
) {
    if (update && !promptUserLL(id, "id"))
        throw ManagerException(ManagerExceptionKind::InvalidUpdateID);

    if (!promptUserString(name, "name") && !update)
        throw ManagerException(ManagerExceptionKind::EmptyAddItem);

    if (update && name.empty())
        throw ManagerException(ManagerExceptionKind::EmptyUpdatePrompt);

    return LibraryItemCategory(id, name);
}

int LibraryManager::parse(int argc, char *argv[]) {
    try {
        app.parse(argc, argv);
    } catch(const CLI::ParseError &e) {
        return app.exit(e);
    }

    arguments_parsed = true;

    return EXIT_SUCCESS;
}

void LibraryManager::finishInit() {
    if (!arguments_parsed)
        return; //throw ManagerException(ManagerExceptionKind::NoArgs);

    libraryDatabase = std::make_unique<SQLiteLibraryDatabase>(appDataFolder, databaseFilename);
    //libraryUI = std::make_unique<FTXUILibraryUI>();

    initialized = true;
}

void LibraryManager::applyDatabaseAdd() {
    if (categoryMode) {
        if (libraryDatabase->saveItemCategory(libraryItemCategory))
            std::cout << "Category sucessfully added to the database!";
        else
            throw ManagerException(ManagerExceptionKind::InvalidItemCategory);
    } else {
        libraryItem = libraryDatabase->fetchFullItem(libraryItem);

        if (libraryDatabase->saveItem(libraryItem))
            std::cout << "Item sucessfully added to the database!";
        else
            throw ManagerException(ManagerExceptionKind::InvalidItem);
    }
}

void LibraryManager::applyDatabaseUpdate() {
    if (categoryMode) {
        if (libraryDatabase->saveItemCategory(libraryItemCategory))
            std::cout << "Category sucessfully updated!";
        else
            throw ManagerException(ManagerExceptionKind::InvalidItemCategory);
    } else {
        libraryItem = libraryDatabase->fetchFullItem(libraryItem);

        if (libraryDatabase->saveItem(libraryItem))
            std::cout << "Item sucessfully updated!";
        else
            throw ManagerException(ManagerExceptionKind::InvalidItem);
    }
}

void LibraryManager::applyDatabaseRemove() {
    if (categoryMode) {
        libraryItemCategory = libraryDatabase->fetchFullItemCategory(libraryItemCategory);

        if (promptItemDeletion())
            libraryDatabase->removeItemCategory(libraryItemCategory);
        else
            std::cout << "Category not deleted !" << std::endl;
    } else {
        libraryItem = libraryDatabase->fetchFullItem(libraryItem);

        if (promptItemDeletion())
            libraryDatabase->removeItem(libraryItem);
        else
            std::cout << "Item not deleted !" << std::endl;
    }
}

void LibraryManager::databaseSearch() {
    if (operationKind == OperationKind::SeachCategory && !elemName.empty()) {
        auto nameResult = searchCategoriesByName();
        itemsCategoryResult.insert(
            itemsCategoryResult.end(),
            std::make_move_iterator(nameResult.begin()),
            std::make_move_iterator(nameResult.end())
        );
    }

    if (operationKind == OperationKind::SearchItem && !elemName.empty()) {
        auto nameResult = searchItemsByName();
        itemSearchResult.insert(
            itemSearchResult.end(),
            std::make_move_iterator(nameResult.begin()),
            std::make_move_iterator(nameResult.end())
        );
    }

    if (operationKind == OperationKind::SearchItem && !elemAuthor.empty()) {
        auto authorResult = searchItemsByAuthor();
        itemSearchResult.insert(
            itemSearchResult.end(),
            std::make_move_iterator(authorResult.begin()),
            std::make_move_iterator(authorResult.end())
        );
    }

    if (operationKind == OperationKind::SearchItem && !searchKeywords.empty()) {
        auto keywordsResult = searchItemsByName();
        itemSearchResult.insert(
            itemSearchResult.end(),
            std::make_move_iterator(keywordsResult.begin()),
            std::make_move_iterator(keywordsResult.end())
        );
    }
}

std::vector<LibraryItem> LibraryManager::searchItemsByName() {
    return libraryDatabase->searchItemsByName(elemName);
}

std::vector<LibraryItem> LibraryManager::searchItemsByAuthor() {
    return libraryDatabase->searchItemsByAuthor(elemAuthor);
}

std::vector<LibraryItem> LibraryManager::searchItemsByKeywords() {
    return libraryDatabase->searchItemsByKeywords(searchKeywords);
}

std::vector<LibraryItemCategory> LibraryManager::searchCategoriesByName() {
    return libraryDatabase->searchCategoriesByName(elemName);
}

void LibraryManager::applyDatabaseChanges() {
    if (!initialized)
        return; //throw ManagerException(ManagerExceptionKind::NotInitialized);

    switch(operationKind) {
        case OperationKind::Add:
            return applyDatabaseAdd();
        case OperationKind::Update:
            return applyDatabaseUpdate();
        case OperationKind::Remove:
            return applyDatabaseRemove();
        case OperationKind::SearchItem:
        case OperationKind::SeachCategory:
            return databaseSearch();
        case OperationKind::None:
        default:
            throw ManagerException("Unsupported yet");
    }
}

void LibraryManager::displayFoundItem() {
    if (!itemSearchResult.empty())
        for (const auto item: itemSearchResult)
            std::cout << item << std::endl;

    if (!itemsCategoryResult.empty())
        for (const auto itemCategory: itemsCategoryResult)
            std::cout << itemCategory << std::endl;
}

bool LibraryManager::promptItemDeletion() {
    std::cout << "Are you sure you want to remove:" << std::endl;
    if (categoryMode)
        std::cout << libraryItemCategory.getName() << " category ?" << std::endl;
    else
        std::cout << libraryItem.getName() << " by " << libraryItem.getAuthor() << " ?" << std::endl;

    try {
        return getYesNoInputWithDefault();
    } catch (std::runtime_error &e) {
        return false;
    }

    return false;
}
