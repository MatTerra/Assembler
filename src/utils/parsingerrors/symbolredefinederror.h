//
// Created by mateusberardo on 10/03/2021.
//

#ifndef MONTADOR_SYMBOLREDEFINEDERROR_H
#define MONTADOR_SYMBOLREDEFINEDERROR_H

#include "parsingerror.h"


class SymbolRedefinedError: public ParsingError {
public:
    explicit SymbolRedefinedError(uint64_t line, std::string symbol);
};


#endif //MONTADOR_SYMBOLREDEFINEDERROR_H
