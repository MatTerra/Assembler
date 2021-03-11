//
// Created by mateusberardo on 05/03/2021.
//

#ifndef MONTADOR_INVALIDOPERANDCOUNTERROR_H
#define MONTADOR_INVALIDOPERANDCOUNTERROR_H


#include "parsingerror.h"

class InvalidOperandCountError : public ParsingError {
public:
    explicit InvalidOperandCountError(uint64_t line, std::string operation);
};


#endif //MONTADOR_INVALIDOPERANDCOUNTERROR_H
