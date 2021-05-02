//
// Created by mateusberardo on 02/05/2021.
//
#include "modulechecker.h"

bool ModuleChecker::check(std::string moduleContent) {
    lowerCaseString(moduleContent);
    bool hasBegin = moduleContent.find("begin") != std::string::npos;
    bool hasEnd = moduleContent.find("end") != std::string::npos;
    return hasBegin && hasEnd;
}
