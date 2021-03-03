//
// Created by mateusberardo on 03/03/2021.
//

#ifndef MONTADOR_STOPOPERATION_H
#define MONTADOR_STOPOPERATION_H

#include "baseoperation.h"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

class StopOperation : public BaseOperation{
public:
    StopOperation(std::vector<std::string> operands)
        :BaseOperation("stop", 1, 14, std::move(operands)){};
    std::string getOutput() override;
};


#endif //MONTADOR_STOPOPERATION_H
