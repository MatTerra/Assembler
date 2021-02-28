//
// Created by mateusberardo on 28/02/2021.
//

#ifndef MONTADOR_ADDOPERATION_H
#define MONTADOR_ADDOPERATION_H

#include "baseoperation.h"
#include <vector>
#include <sstream>
#include <iomanip>

class AddOperation : public BaseOperation{
public:
    AddOperation(std::vector<uint16_t> operands)
        :BaseOperation("add", 2, 1, std::move(operands)){};
    std::string getOutput() override;
};


#endif //MONTADOR_ADDOPERATION_H
