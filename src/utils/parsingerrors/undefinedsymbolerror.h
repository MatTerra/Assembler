//
// Created by mateusberardo on 05/03/2021.
//

#ifndef MONTADOR_UNDEFINEDSYMBOLERROR_H
#define MONTADOR_UNDEFINEDSYMBOLERROR_H

#include <stdexcept>
#include <cstdint>
#include <string>
#include <sstream>
#include "parsingerrors/parsingerror.h"

class UndefinedSymbolError : public ParsingError {
public:
    explicit UndefinedSymbolError(uint16_t line,
                                  std::string symbol);
};


#endif //MONTADOR_UNDEFINEDSYMBOLERROR_H
