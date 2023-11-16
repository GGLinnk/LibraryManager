#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

enum class DatabaseExceptionKind {
    ItemAlreadyExists,
    ItemDontExits,
};

class DatabaseException : public std::exception {
private:
    DatabaseExceptionKind kind;
    std::string message;

    void setMessage();

public: 
    DatabaseException(DatabaseExceptionKind kind);
    const char* what() const noexcept override;
};