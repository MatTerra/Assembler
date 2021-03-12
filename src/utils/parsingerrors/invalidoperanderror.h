//
// Created by mateusberardo on 12/03/2021.
//

#ifndef MONTADOR_INVALIDOPERANDERROR_H
#define MONTADOR_INVALIDOPERANDERROR_H


#include "parsingerror.h"

class InvalidOperandError : public ParsingError {
public:
    explicit InvalidOperandError(uint64_t line, std::string operand);
};


#endif //MONTADOR_INVALIDOPERANDERROR_H
