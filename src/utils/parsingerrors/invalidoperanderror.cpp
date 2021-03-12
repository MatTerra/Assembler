//
// Created by mateusberardo on 12/03/2021.
//

#include "invalidoperanderror.h"

InvalidOperandError::InvalidOperandError(uint64_t line, std::string operand)
        : ParsingError(line, "Semantic Error") {
    std::ostringstream what_arg_stream;
    what_arg_stream << "Invalid operand \""
                    << operand << "\"";
    what_arg = what_arg_stream.str();
}