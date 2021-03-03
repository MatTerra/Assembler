//
// Created by mateusberardo on 03/03/2021.
//

#ifndef MONTADOR_COPYOPERATION_H
#define MONTADOR_COPYOPERATION_H

#include "baseoperation.h"
#include <vector>
#include <sstream>
#include <iomanip>

class CopyOperation : public BaseOperation{
public:
    CopyOperation(std::vector<uint16_t> operands)
        :BaseOperation("copy", 3, 9, std::move(operands)){};
    std::string getOutput() override;
};


#endif //MONTADOR_COPYOPERATION_H
