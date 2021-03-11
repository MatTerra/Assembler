//
// Created by mateusberardo on 10/03/2021.
//

#include "symbolredefinederror.h"

SymbolRedefinedError::SymbolRedefinedError(uint64_t line,
                                           std::string symbol)
        : ParsingError(line, "Semantic Error"){
    std::ostringstream what_arg_stream;
    what_arg_stream << "Redefinition of symbol \""
                    << symbol << "\"";
    what_arg = what_arg_stream.str();
}
