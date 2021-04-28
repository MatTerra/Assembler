//
// Created by mateusberardo on 12/03/2021.
//

#include "missinglabelerror.h"

MissingLabelError::MissingLabelError(uint64_t line)
        : ParsingError(line, "Syntax Error") {
    std::ostringstream what_arg_stream;
    what_arg_stream << "Extern must be used with a label!";
    what_arg = what_arg_stream.str();
}