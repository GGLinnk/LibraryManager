#include <string>
#include <iostream>
#include <algorithm>

bool getYesNoInputWithDefault(bool defaultValue = false, int maxTries = 3, bool hasDefault = true);
bool promptUserString(std::string& itemVar, const char* itemVarName, size_t maxtries = 3);
bool promptUserLL(long long& promptVar, const char* itemVarName, size_t maxtries = 3);