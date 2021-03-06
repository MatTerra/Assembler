//
// Created by mateusberardo on 03/03/2021.
//

#ifndef MONTADOR_LOADOPERATION_H
#define MONTADOR_LOADOPERATION_H

#include "baseoperation.h"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

class LoadOperation : public BaseOperation{
public:
    LoadOperation(std::vector<std::string> operands)
        :BaseOperation("load", 2, 10, std::move(operands)){};
    std::string getOutput() override;
};


#endif //MONTADOR_LOADOPERATION_H
