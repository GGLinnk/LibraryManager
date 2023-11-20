#include "LibraryItemCategory.h"

LibraryItemCategory::LibraryItemCategory() : LibraryItemCategory(0, std::string()) {}

LibraryItemCategory::LibraryItemCategory(const std::string& name) {
    try {
        id = std::stoll(name);
    } catch (...) { // FIXME !
        this->name = name;
    }
    empty = (id <= 0 && name.empty()) ? true : false;
}

LibraryItemCategory::LibraryItemCategory(long long id)
: LibraryItemCategory(id, std::string("")) { }

LibraryItemCategory::LibraryItemCategory(long long id, const std::string& name)
: id(id), name(name) {
    empty = (id <= 0 && name.empty()) ? true : false;
    initialized = (id >= 0 && !name.empty()) ? true : false;
}

bool LibraryItemCategory::isInitialized() const {
    return initialized;
}

long long LibraryItemCategory::getId() const {
    return id;
}

const std::string& LibraryItemCategory::getName() const {
    return name;
}

bool LibraryItemCategory::isEmpty() const {
    return empty;
}