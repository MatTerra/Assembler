//
// Created by mateusberardo on 05/03/2021.
//

#ifndef MONTADOR_UNDEFINEDSYMBOLEXCEPTION_H
#define MONTADOR_UNDEFINEDSYMBOLEXCEPTION_H

#include <stdexcept>
#include <cstdint>
#include <string>
#include <sstream>
#include "parsingexception.h"

class UndefinedSymbolException : public ParsingException {
public:
    explicit UndefinedSymbolException(uint16_t line,
                                      std::string symbol);
};


#endif //MONTADOR_UNDEFINEDSYMBOLEXCEPTION_H
