#pragma once

#include <string>

enum ItemKind {
    NONE,
    BOOK,
    MOVIE,
    AUDIO
};

class LibraryItem  {
private:
    ItemKind kind;
    long int id;
    std::string name;
    std::string author;
    std::string description;

public:
    LibraryItem(int id, const std::string &name, const std::string &author, const std::string &description, ItemKind kind);

    // Getters
    int getId() const;
    const std::string &getName() const;
    const std::string &getAuthor() const;
    const std::string &getDescription() const;
    ItemKind getKind() const;

    bool set_kind();
};