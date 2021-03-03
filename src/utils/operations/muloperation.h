//
// Created by mateusberardo on 03/03/2021.
//

#ifndef MONTADOR_MULOPERATION_H
#define MONTADOR_MULOPERATION_H

#include "baseoperation.h"
#include <vector>
#include <sstream>
#include <iomanip>

class MulOperation : public BaseOperation{
public:
    MulOperation(std::vector<uint16_t> operands)
        :BaseOperation("mul", 2, 3, std::move(operands)){};
    std::string getOutput() override;
};


#endif //MONTADOR_MULOPERATION_H
