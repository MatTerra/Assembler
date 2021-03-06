//
// Created by mateusberardo on 03/03/2021.
//

#ifndef MONTADOR_JMPNOPERATION_H
#define MONTADOR_JMPNOPERATION_H

#include "baseoperation.h"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

class JmpnOperation : public BaseOperation{
public:
    JmpnOperation(std::vector<std::string> operands)
        :BaseOperation("jmpn", 2, 6, std::move(operands)){};
    std::string getOutput() override;
};


#endif //MONTADOR_JMPNOPERATION_H
