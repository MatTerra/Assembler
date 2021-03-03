//
// Created by mateusberardo on 03/03/2021.
//


#include "stopoperation.h"

std::string StopOperation::getOutput() {
    std::ostringstream output;
    output << std::setfill('0') << std::setw(2) <<  opCode;
    return output.str();
}