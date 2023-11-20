#include "LibraryItemKind.h"

ItemKind::ItemKind() : ItemKind(0, std::string()) {}

ItemKind::ItemKind(const std::string& name) {
    try {
        id = std::stoll(name);
    } catch (...) {
        this->name = name;
    }
}

ItemKind::ItemKind(long long id)
: ItemKind(id, std::string("")) { }

ItemKind::ItemKind(long long id, const std::string& name)
: id(id), name(name) {
    empty = (id <= 0 && name.empty()) ? true : false;
    initialized = (id >= 0 && !name.empty()) ? true : false;
}

bool ItemKind::isInitialized() const {
    return initialized;
}

long long ItemKind::getId() const {
    return id;
}

const std::string& ItemKind::getName() const {
    return name;
}

bool ItemKind::isEmpty() const {
    return empty;
}