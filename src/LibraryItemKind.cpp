#include "LibraryItemKind.h"

ItemKind::ItemKind(long int id, const std::string &name) : id(id), name(name) {}

long int ItemKind::getId() const {
    return id;
}

const std::string& ItemKind::getName() const {
    return name;
}