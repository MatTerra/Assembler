//
// Created by mateusberardo on 28/04/2021.
//

#include "externoperation.h"

std::string ExternOperation::getOutput() {
    return std::string();
}

bool ExternOperation::isValid() {
    return operands.size() == 0;
}
