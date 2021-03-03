//
// Created by mateusberardo on 03/03/2021.
//

#ifndef MONTADOR_JMPZOPERATION_H
#define MONTADOR_JMPZOPERATION_H

#include "baseoperation.h"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

class JmpzOperation : public BaseOperation{
public:
    JmpzOperation(std::vector<std::string> operands)
        :BaseOperation("jmpz", 2, 8, std::move(operands)){};
    std::string getOutput() override;
};


#endif //MONTADOR_JMPZOPERATION_H
