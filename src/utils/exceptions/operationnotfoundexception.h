//
// Created by mateusberardo on 28/02/2021.
//

#ifndef MONTADOR_OPERATIONNOTFOUNDEXCEPTION_H
#define MONTADOR_OPERATIONNOTFOUNDEXCEPTION_H

#include <stdexcept>
#include <string>

class OperationNotFoundException : public std::runtime_error {
public:
    explicit OperationNotFoundException(std::string what_arg);
};


#endif //MONTADOR_OPERATIONNOTFOUNDEXCEPTION_H
