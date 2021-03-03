//
// Created by mateusberardo on 03/03/2021.
//


#include "jmpzoperation.h"

std::string JmpzOperation::getOutput() {
    std::ostringstream output;
    output << std::setfill('0') << std::setw(2) <<  opCode << " "
            << std::setfill('0') << std::setw(2) << operands[0];
    return output.str();
}