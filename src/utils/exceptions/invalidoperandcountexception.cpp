//
// Created by mateusberardo on 05/03/2021.
//

#include "invalidoperandcountexception.h"

InvalidOperandCountException::InvalidOperandCountException(uint16_t line,
                                                           std::string operation)
        :ParsingException(line, "Semantic Error"){
    std::ostringstream what_arg_stream;
    what_arg_stream << "Invalid operand count for operation \""
        << operation << "\"";
    what_arg = what_arg_stream.str();
}
