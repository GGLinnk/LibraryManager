#include "helpers.h"

bool isYes(const std::string& input) {
    // Convert input to uppercase for case-insensitive comparison
    std::string uppercaseInput = input;
    std::transform(uppercaseInput.begin(), uppercaseInput.end(), uppercaseInput.begin(), ::toupper);

    return (uppercaseInput == "Y" || uppercaseInput == "YES");
}

bool isNo(const std::string& input) {
    // Convert input to uppercase for case-insensitive comparison
    std::string uppercaseInput = input;
    std::transform(uppercaseInput.begin(), uppercaseInput.end(), uppercaseInput.begin(), ::toupper);

    return (uppercaseInput == "N" || uppercaseInput == "NO");
}

bool getYesNoInputWithDefault(bool defaultValue, int maxTries, bool hasDefault) {
    std::string prompt;

    if (hasDefault)
        prompt = std::string("Do you want to proceed? (").append((defaultValue ? "Y/n" : "y/N")).append("): ");
    else
        prompt = "Do you want to proceed? (y/n): ";

    for (int attempt = 1; attempt <= maxTries; ++attempt) {
        std::string input;

        std::cout << prompt;
        std::getline(std::cin, input);

        if (input.empty()) {
            return defaultValue;
        } else if (isYes(input)) {
            return true;
        } else if (isNo(input)) {
            return false;
        } else {
            std::cout << "Invalid input. Please enter 'Y' or 'N'." << std::endl;
        }
    }

    throw std::runtime_error("Exceeded maximum number of attempts. Aborting.");
}

bool getMissingInfo(long int id, std::string& itemVar, char* itemVarName) {
    for (short tries = 0; itemVar.empty() && tries <= 3; tries++) {
        if (tries > 0)
            std::cout << "Please enter a valid " << itemVarName << "! (" << tries << "/3)" << std::endl;
        std::cout << "Enter " << itemVarName << ": ";
        std::getline(std::cin, itemVar);
        if (id > 0)
            return true;
    }

    return !itemVar.empty();
}