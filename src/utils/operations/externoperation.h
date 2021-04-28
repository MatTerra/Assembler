//
// Created by mateusberardo on 28/04/2021.
//

#ifndef MONTADOR_EXTERNOPERATION_H
#define MONTADOR_EXTERNOPERATION_H

#include "baseoperation.h"
#include <utility>
#include <vector>
#include <string>

class ExternOperation : public BaseOperation{
public:
    ExternOperation(std::vector<std::string> operands)
        : BaseOperation("extern", 0, 0, std::move(operands)){}
    std::string getOutput() override;
    bool isValid() override;
};


#endif //MONTADOR_EXTERNOPERATION_H
