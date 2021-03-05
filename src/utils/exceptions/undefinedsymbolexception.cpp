//
// Created by mateusberardo on 05/03/2021.
//


#include "undefinedsymbolexception.h"

UndefinedSymbolException::UndefinedSymbolException(uint16_t line,
                                                   std::string symbol)
        : ParsingException(line, "Semantic Error") {
    std::ostringstream what_arg_stream;
    what_arg_stream << "Undefined symbol \"" << symbol << "\"";
    what_arg = what_arg_stream.str();
}
