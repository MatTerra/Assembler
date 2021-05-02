//
// Created by mateusberardo on 28/04/2021.
//

#include "publicoperation.h"

std::string PublicOperation::getOutput() {
    return std::string();
}

bool PublicOperation::isValid() {
    return operands.size() == 1;
}
