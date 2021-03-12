//
// Created by mateusberardo on 12/03/2021.
//

#ifndef MONTADOR_INVALIDLABELERROR_H
#define MONTADOR_INVALIDLABELERROR_H


#include "parsingerror.h"

class InvalidLabelError : public ParsingError {
public:
    explicit InvalidLabelError(uint64_t line, std::string label);
};


#endif //MONTADOR_INVALIDLABELERROR_H
