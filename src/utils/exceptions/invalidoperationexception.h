//
// Created by mateusberardo on 05/03/2021.
//

#ifndef MONTADOR_INVALIDOPERATIONEXCEPTION_H
#define MONTADOR_INVALIDOPERATIONEXCEPTION_H


#include <stdexcept>
#include <string>

class InvalidOperationException : public std::runtime_error {
public:
    explicit InvalidOperationException(std::string what_arg);
};


#endif //MONTADOR_INVALIDOPERATIONEXCEPTION_H
