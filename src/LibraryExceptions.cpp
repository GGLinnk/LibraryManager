#include "LibraryExceptions.h"

DatabaseException::DatabaseException(DatabaseExceptionKind kind) : kind(kind) {
    setMessage();
}

void DatabaseException::setMessage() {
    switch (kind) {
        case DatabaseExceptionKind::ItemAlreadyExists:
            message = "Item already exists in database";
            break;
        case DatabaseExceptionKind::ItemDontExits:
            message = "Database query error.";
            break;

        default:
            message = "Unknown database exception.";
    }
}

const char* DatabaseException::what() const noexcept {
    return message.c_str();
}