#include <string>
#include <iostream>
#include <algorithm>

bool getYesNoInputWithDefault(bool defaultValue = false, int maxTries = 3, bool hasDefault = true);
bool getMissingInfo(long long id, std::string& itemVar, char* itemVarName);