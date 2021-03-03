//
// Created by mateusberardo on 02/03/2021.
//

#ifndef MONTADOR_SUBOPERATION_H
#define MONTADOR_SUBOPERATION_H

#include "baseoperation.h"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

class SubOperation : public BaseOperation{
public:
    SubOperation(std::vector<std::string> operands)
        :BaseOperation("sub", 2, 2, std::move(operands)){};
    std::string getOutput() override;
};


#endif //MONTADOR_SUBOPERATION_H
