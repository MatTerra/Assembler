//
// Created by mateusberardo on 05/03/2021.
//

#include "invalidoperationexception.h"

InvalidOperationException::InvalidOperationException(std::string what_arg)
    :std::runtime_error(what_arg){
}
