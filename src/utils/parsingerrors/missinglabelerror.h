//
// Created by mateusberardo on 12/03/2021.
//

#ifndef MONTADOR_MISSINGLABELERROR_H
#define MONTADOR_MISSINGLABELERROR_H


#include "parsingerror.h"

class MissingLabelError : public ParsingError {
public:
    explicit MissingLabelError(uint64_t line);
};


#endif //MONTADOR_MISSINGLABELERROR_H
