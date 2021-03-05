//
// Created by mateusberardo on 05/03/2021.
//

#ifndef MONTADOR_INVALIDOPERANDCOUNTEXCEPTION_H
#define MONTADOR_INVALIDOPERANDCOUNTEXCEPTION_H


#include "parsingexception.h"

class InvalidOperandCountException : public ParsingException {
public:
    explicit InvalidOperandCountException(uint16_t line, std::string operation);
};


#endif //MONTADOR_INVALIDOPERANDCOUNTEXCEPTION_H
