//
// Created by mateusberardo on 02/05/2021.
//
#include "programchecker.h"

bool ProgramChecker::check(std::string programContent) {
    lowerCaseString(programContent);
    bool hasBegin = programContent.find("begin") != std::string::npos;
    bool hasEnd = programContent.find("end") != std::string::npos;
    return !(hasBegin || hasEnd);
}
