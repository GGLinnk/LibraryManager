#include "LibraryItem.h"

LibraryItem::LibraryItem() {}

LibraryItem::LibraryItem(long int id)
: empty(false) { }

LibraryItem::LibraryItem(const std::string& name, const std::string& author, const std::string& description, ItemKind itemKind)
: LibraryItem(0, name, author, description, itemKind) { }

LibraryItem::LibraryItem(long int id, const std::string& name, const std::string& author, const std::string& description, ItemKind itemKind)
: id(id), name(name), author(author), description(description), itemKind(itemKind) {
    empty = (id <= 0 && name.empty() && author.empty() && description.empty() && itemKind.isEmpty()) ? true : false;
    initialized = (id >= 0 && !name.empty() && !author.empty() && !description.empty() && itemKind.isInitialized()) ? true : false;
}

long int LibraryItem::getId() const {
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

ItemKind LibraryItem::getItemKind() const {
    return itemKind;
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
