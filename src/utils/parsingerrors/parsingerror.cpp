//
// Created by mateusberardo on 05/03/2021.
//

#include "parsingerror.h"

std::string ParsingError::what() {
    std::ostringstream output;
    output << errorType << ": " << what_arg << " in line " << line << ".";
    return output.str();
}
