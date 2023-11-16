#include "LibraryItem.h"

LibraryItem::LibraryItem() {}

LibraryItem::LibraryItem(long int id, const std::string& name, const std::string& author, const std::string& description, ItemKind itemKind)
    : id(id), name(name), author(author), description(description), itemKind(itemKind) {}

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
