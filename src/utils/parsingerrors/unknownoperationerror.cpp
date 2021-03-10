//
// Created by mateusberardo on 05/03/2021.
//

#include "unknownoperationerror.h"
UnknownOperationError::UnknownOperationError(uint16_t line,
                                             std::string mnemonic)
        : ParsingError(line, "Lexical Error") {
    std::ostringstream what_arg_stream;
    what_arg_stream << "Unknown mnemonic \"" << mnemonic << "\"";
    what_arg = what_arg_stream.str();
}
