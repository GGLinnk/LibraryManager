#include "LibraryExceptions.h"

ManagerException::ManagerException()
: ManagerException(ManagerExceptionKind::UserAborted) {}

ManagerException::ManagerException(ManagerExceptionKind reason)
: reason(reason), std::runtime_error(getMessage(reason)) { }

ManagerException::ManagerException(ManagerExceptionKind reason, const std::string& addMessage)
: reason(reason), std::runtime_error(getMessage(reason).append("\n").append(addMessage)) { }

ManagerException::ManagerException(const std::string& message)
: std::runtime_error(message) {}

ManagerException::ManagerException(const char* message)
: std::runtime_error(message) {}

const ManagerExceptionKind ManagerException::getExceptionKind() const {
    return reason;
}

std::string ManagerException::getMessage(ManagerExceptionKind reason) {
    switch (reason)
    {
    case ManagerExceptionKind::CLIEmptyString:
        return std::string("Invalid argument!");
    case ManagerExceptionKind::CLIParseError:
        return std::string("Failed to Parse CLI!");
    case ManagerExceptionKind::DBCategoryAlreadyExists:
        return std::string("Category already exists!");
    case ManagerExceptionKind::DBCategoryNotFound:
        return std::string("Category not found!");
    case ManagerExceptionKind::DBItemAlreadyExists:
        return std::string("Item already exists!");
    case ManagerExceptionKind::DBItemNotFound:
        return std::string("Item not found!");
    case ManagerExceptionKind::DBEntryNotFound:
        return std::string("Database entry not found!");
    case ManagerExceptionKind::DBException:
        return std::string("Database exception found!");
    case ManagerExceptionKind::DBInitFail:
        return std::string("Database init fail!");
    case ManagerExceptionKind::EmptyUpdatePrompt:
        return std::string("Not enough data to update item!");
    case ManagerExceptionKind::EmptyAddItem:
        return std::string("Not enough data to add item!");
    case ManagerExceptionKind::FSFileNotCreated:
        return std::string("Failed to create file!");
    case ManagerExceptionKind::FSDirectoryNotCreated:
        return std::string("Failed to create directory!");
    case ManagerExceptionKind::FSNotADirectory:
        return std::string("Not a directory!");
    case ManagerExceptionKind::InvalidItem:
        return std::string("Invalid Item!");
    case ManagerExceptionKind::InvalidItemID:
        return std::string("Invalid ID!");
    case ManagerExceptionKind::InvalidItemKind:
        return std::string("Invalid Item Kind!");
    case ManagerExceptionKind::InvalidUpdateID:
        return std::string("Invalid Update ID!");
    case ManagerExceptionKind::ItemNotInitialized:
        return std::string("Library Item is not initialized!");
    case ManagerExceptionKind::LibraryItemKindNotFound:
        return std::string("Library item kind not found!");
    case ManagerExceptionKind::LibraryItemNotFound:
        return std::string("Library item not found!");
    case ManagerExceptionKind::NoArgs:
        return std::string("No arguments parsed!");
    case ManagerExceptionKind::UserAborted:
        return std::string("Operation aborted by user!");
    default:
        return std::string("Unsupported abort!");
    }
}

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