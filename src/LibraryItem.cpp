#include "LibraryItem.h"

LibraryItem::LibraryItem() {}

LibraryItem::LibraryItem(long long id)
: empty(false) { }

LibraryItem::LibraryItem(const std::string& name, const std::string& author, const std::string& description, LibraryItemCategory libraryItemCategory)
: LibraryItem(0, name, author, description, libraryItemCategory) { }

LibraryItem::LibraryItem(long long id, const std::string& name, const std::string& author, const std::string& description, LibraryItemCategory libraryItemCategory)
: id(id), name(name), author(author), description(description), libraryItemCategory(libraryItemCategory) {
    empty = (id <= 0 && name.empty() && author.empty() && description.empty() && libraryItemCategory.isEmpty()) ? true : false;
    initialized = (id >= 0 && !name.empty() && !author.empty() && !description.empty() && libraryItemCategory.isInitialized()) ? true : false;
}

long long LibraryItem::getId() const {
    return id;
}

const std::string& LibraryItem::getName() const {
    return name;
}

const std::string& LibraryItem::getAuthor() const {
    return author;
}

const std::string& LibraryItem::getDescription() const {
    return description;
}

LibraryItemCategory LibraryItem::getItemCategory() const {
    return libraryItemCategory;
}

void LibraryItem::setInitialized() {
    initialized = true;
}

bool LibraryItem::isInitialized() const {
    return initialized;
}

bool LibraryItem::isEmpty() const {
    return empty;
}
