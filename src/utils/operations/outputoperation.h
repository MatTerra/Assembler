//
// Created by mateusberardo on 03/03/2021.
//

#ifndef MONTADOR_OUTPUTOPERATION_H
#define MONTADOR_OUTPUTOPERATION_H

#include "baseoperation.h"
#include <vector>
#include <sstream>
#include <iomanip>

class OutputOperation : public BaseOperation{
public:
    OutputOperation(std::vector<uint16_t> operands)
        :BaseOperation("output", 2, 13, std::move(operands)){};
    std::string getOutput() override;
};


#endif //MONTADOR_OUTPUTOPERATION_H
