//
// Created by mateusberardo on 03/03/2021.
//

#ifndef MONTADOR_INPUTOPERATION_H
#define MONTADOR_INPUTOPERATION_H

#include "baseoperation.h"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

class InputOperation : public BaseOperation{
public:
    InputOperation(std::vector<std::string> operands)
        :BaseOperation("input", 2, 12, std::move(operands)){};
    std::string getOutput() override;
};


#endif //MONTADOR_INPUTOPERATION_H
