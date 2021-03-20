//
// Created by mateusberardo on 12/03/2021.
//

#include "invalidlabelerror.h"

InvalidLabelError::InvalidLabelError(uint64_t line, std::string label)
        : ParsingError(line, "Lexical Error") {
    std::ostringstream what_arg_stream;
    what_arg_stream << "Invalid label \""
                    << label << "\"";
    what_arg = what_arg_stream.str();
}