//
// Created by mateusberardo on 10/03/2021.
//

#include "symbolinvalidexception.h"

SymbolInvalidException::SymbolInvalidException(std::string what_arg)
    : std::runtime_error(what_arg) {

}
