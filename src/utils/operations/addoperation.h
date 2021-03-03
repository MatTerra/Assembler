//
// Created by mateusberardo on 28/02/2021.
//

#ifndef MONTADOR_ADDOPERATION_H
#define MONTADOR_ADDOPERATION_H

#include "baseoperation.h"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

class AddOperation : public BaseOperation{
public:
    AddOperation(std::vector<std::string> operands)
        :BaseOperation("add", 2, 1, std::move(operands)){};
    std::string getOutput() override;
};


#endif //MONTADOR_ADDOPERATION_H
