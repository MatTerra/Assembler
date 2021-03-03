//
// Created by mateusberardo on 03/03/2021.
//


#include "copyoperation.h"

std::string CopyOperation::getOutput() {
    std::ostringstream output;
    output << std::setfill('0') << std::setw(2) <<  opCode << " "
            << std::setfill('0') << std::setw(2) << operands[0] << " "
            << std::setfill('0') << std::setw(2) << operands[1];
    return output.str();
}