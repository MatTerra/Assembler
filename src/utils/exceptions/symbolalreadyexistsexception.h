//
// Created by mateusberardo on 10/03/2021.
//

#ifndef MONTADOR_SYMBOLALREADYEXISTSEXCEPTION_H
#define MONTADOR_SYMBOLALREADYEXISTSEXCEPTION_H

#include <string>
#include <stdexcept>

class SymbolAlreadyExistsException : public std::runtime_error{
public:
    explicit SymbolAlreadyExistsException(std::string what_arg);
};


#endif //MONTADOR_SYMBOLALREADYEXISTSEXCEPTION_H
