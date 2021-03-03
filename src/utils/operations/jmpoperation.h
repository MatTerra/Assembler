//
// Created by mateusberardo on 03/03/2021.
//

#ifndef MONTADOR_JMPOPERATION_H
#define MONTADOR_JMPOPERATION_H

#include "baseoperation.h"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

class JmpOperation : public BaseOperation{
public:
    JmpOperation(std::vector<std::string> operands)
        :BaseOperation("jmp", 2, 5, std::move(operands)){};
    std::string getOutput() override;
};


#endif //MONTADOR_JMPOPERATION_H
