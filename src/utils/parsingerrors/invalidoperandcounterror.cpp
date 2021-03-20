//
// Created by mateusberardo on 05/03/2021.
//

#include "invalidoperandcounterror.h"

InvalidOperandCountError::InvalidOperandCountError(uint64_t line,
                                                   std::string operation)
        : ParsingError(line, "Syntax Error"){
    std::ostringstream what_arg_stream;
    what_arg_stream << "Invalid operand count for operation \""
        << operation << "\"";
    what_arg = what_arg_stream.str();
}
