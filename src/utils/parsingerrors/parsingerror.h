//
// Created by mateusberardo on 05/03/2021.
//

#ifndef MONTADOR_PARSINGERROR_H
#define MONTADOR_PARSINGERROR_H

#include <string>
#include <sstream>
#include <utility>

class ParsingError {
public:
    explicit ParsingError(uint64_t line, std::string errorType)
        :line(line), errorType(std::move(errorType)){};
    std::string what();

protected:
    std::string what_arg;
    std::string errorType;

private:
    uint16_t line;
};


#endif //MONTADOR_PARSINGERROR_H
