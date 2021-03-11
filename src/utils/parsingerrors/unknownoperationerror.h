//
// Created by mateusberardo on 05/03/2021.
//

#ifndef MONTADOR_UNKNOWNOPERATIONERROR_H
#define MONTADOR_UNKNOWNOPERATIONERROR_H

#include "parsingerrors/parsingerror.h"

class UnknownOperationError : public ParsingError {
public:
    explicit UnknownOperationError(uint64_t line, std::string mnemonic);
};


#endif //MONTADOR_UNKNOWNOPERATIONERROR_H
