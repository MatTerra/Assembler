//
// Created by mateusberardo on 10/03/2021.
//

#ifndef MONTADOR_SYMBOLINVALIDEXCEPTION_H
#define MONTADOR_SYMBOLINVALIDEXCEPTION_H

#include <string>
#include <stdexcept>

class SymbolInvalidException : public std::runtime_error{
public:
    explicit SymbolInvalidException(std::string what_arg);
};


#endif //MONTADOR_SYMBOLINVALIDEXCEPTION_H
