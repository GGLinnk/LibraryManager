#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

enum ManagerExceptionKind {
    _ = 200,
    CLIEmptyString,
    CLIParseError,
    CustomAbort,
    DBEntryNotFound,
    DBInitFail,
    EmptyUpdatePrompt,
    EmptyAddItem,
    FSFileNotCreated,
    FSDirectoryNotCreated,
    FSNotADirectory,
    InvalidItemID,
    InvalidItemKind,
    InvalidUpdateID,
    LibraryInvalidItem,
    LibraryItemKindNotFound,
    LibraryItemNotFound,
    NoArgs,
    UserAborted,
};

class ManagerException : public std::runtime_error {
public:
    ManagerException();
    ManagerException(ManagerExceptionKind reason, const std::string& addMessage);
    ManagerException(ManagerExceptionKind reason);
    ManagerException(const std::string& message);
    ManagerException(const char* message);

    const ManagerExceptionKind getExceptionKind() const;

private:
    std::string message;
    ManagerExceptionKind reason = ManagerExceptionKind::CustomAbort;

    std::string getMessage(ManagerExceptionKind reason);
};

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