#include "LibraryItemKind.h"

ItemKind::ItemKind() : ItemKind(0, std::string()) {
    empty = true;
}

ItemKind::ItemKind(const std::string &name) : ItemKind(0, name) { }
ItemKind::ItemKind(long int id) : ItemKind(id, std::string("")) { }

ItemKind::ItemKind(long int id, const std::string &name) : id(id), name(name) {
    if (id > 0 && !name.empty())
        initialized = true;
}

bool ItemKind::isInitialized() const {
    return initialized;
}

long int ItemKind::getId() const {
    return id;
}

const std::string& ItemKind::getName() const {
    return name;
}

bool ItemKind::isEmpty() const {
    return empty;
}