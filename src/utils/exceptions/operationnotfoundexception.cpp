//
// Created by mateusberardo on 28/02/2021.
//

#include "operationnotfoundexception.h"

OperationNotFoundException::OperationNotFoundException(std::string what_arg)
:std::runtime_error(what_arg){}
