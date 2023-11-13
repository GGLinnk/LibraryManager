#include "LibraryItem.h"

LibraryItem::LibraryItem(int id, const std::string& name, const std::string& author, const std::string& description, ItemKind kind)
    : id(id), name(name), author(author), description(description), kind(kind) {}

int LibraryItem::getId() const {
    return id;
}

const std::string &LibraryItem::getName() const {
    return name;
}

const std::string &LibraryItem::getAuthor() const {
    return author;
}

const std::string &LibraryItem::getDescription() const {
    return description;
}

ItemKind LibraryItem::getKind() const {
    return kind;
}
