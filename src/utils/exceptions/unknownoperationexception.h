//
// Created by mateusberardo on 05/03/2021.
//

#ifndef MONTADOR_UNKNOWNOPERATIONEXCEPTION_H
#define MONTADOR_UNKNOWNOPERATIONEXCEPTION_H

#include "parsingexception.h"

class UnknownOperationException : public ParsingException {
public:
    explicit UnknownOperationException(uint16_t line, std::string mnemonic);
};


#endif //MONTADOR_UNKNOWNOPERATIONEXCEPTION_H
