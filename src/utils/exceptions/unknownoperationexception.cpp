//
// Created by mateusberardo on 05/03/2021.
//

#include "unknownoperationexception.h"
UnknownOperationException::UnknownOperationException(uint16_t line,
                                                   std::string mnemonic)
        : ParsingException(line, "Lexical Error") {
    std::ostringstream what_arg_stream;
    what_arg_stream << "Unknown mnemonic \"" << mnemonic << "\"";
    what_arg = what_arg_stream.str();
}
