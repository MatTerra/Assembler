//
// Created by mateusberardo on 28/04/2021.
//

#ifndef MONTADOR_PUBLICOPERATION_H
#define MONTADOR_PUBLICOPERATION_H

#include "baseoperation.h"
#include <utility>
#include <vector>
#include <string>

class PublicOperation : public BaseOperation{
public:
    PublicOperation(std::vector<std::string> operands)
        : BaseOperation("public", 0, 0, std::move(operands)){}
    std::string getOutput() override;
    bool isValid() override;
};


#endif //MONTADOR_PUBLICOPERATION_H
