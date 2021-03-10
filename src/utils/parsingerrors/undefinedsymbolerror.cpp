//
// Created by mateusberardo on 05/03/2021.
//


#include "undefinedsymbolerror.h"

UndefinedSymbolError::UndefinedSymbolError(uint16_t line,
                                           std::string symbol)
        : ParsingError(line, "Semantic Error") {
    std::ostringstream what_arg_stream;
    what_arg_stream << "Undefined symbol \"" << symbol << "\"";
    what_arg = what_arg_stream.str();
}
