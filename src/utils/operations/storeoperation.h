//
// Created by mateusberardo on 03/03/2021.
//

#ifndef MONTADOR_STOREOPERATION_H
#define MONTADOR_STOREOPERATION_H

#include "baseoperation.h"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

class StoreOperation : public BaseOperation{
public:
    StoreOperation(std::vector<std::string> operands)
        :BaseOperation("store", 2, 11, std::move(operands)){};
    std::string getOutput() override;
};


#endif //MONTADOR_STOREOPERATION_H
