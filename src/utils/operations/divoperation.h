//
// Created by mateusberardo on 03/03/2021.
//

#ifndef MONTADOR_DIVOPERATION_H
#define MONTADOR_DIVOPERATION_H

#include "baseoperation.h"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

class DivOperation : public BaseOperation{
public:
    DivOperation(std::vector<std::string> operands)
        :BaseOperation("div", 2, 4, std::move(operands)){};
    std::string getOutput() override;
};


#endif //MONTADOR_DIVOPERATION_H
