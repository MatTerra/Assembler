//
// Created by mateusberardo on 28/02/2021.
//

#include "symbolnotfoundexception.h"

SymbolNotFoundException::SymbolNotFoundException(std::string what_arg)
:std::runtime_error(what_arg){}
