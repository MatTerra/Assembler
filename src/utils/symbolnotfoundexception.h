//
// Created by mateusberardo on 28/02/2021.
//

#ifndef MONTADOR_SYMBOLNOTFOUNDEXCEPTION_H
#define MONTADOR_SYMBOLNOTFOUNDEXCEPTION_H

#include <stdexcept>
#include <string>

class SymbolNotFoundException : public std::runtime_error {
public:
    explicit SymbolNotFoundException(std::string what_arg);
};


#endif //MONTADOR_SYMBOLNOTFOUNDEXCEPTION_H
