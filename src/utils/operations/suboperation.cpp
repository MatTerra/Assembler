//
// Created by mateusberardo on 02/03/2021.
//


#include "suboperation.h"

std::string SubOperation::getOutput() {
    std::ostringstream output;
    output << std::setfill('0') << std::setw(2) <<  opCode << " "
            << std::setfill('0') << std::setw(2) << operands[0];
    return output.str();
}