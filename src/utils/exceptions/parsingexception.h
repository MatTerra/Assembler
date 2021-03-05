//
// Created by mateusberardo on 05/03/2021.
//

#ifndef MONTADOR_PARSINGEXCEPTION_H
#define MONTADOR_PARSINGEXCEPTION_H

#include <string>
#include <sstream>

class ParsingException : public std::exception{
public:
    explicit ParsingException(uint16_t line, std::string errorType)
        :line(line), errorType(errorType){};
    std::string what();

protected:
    std::string what_arg;
    std::string errorType;

private:
    uint16_t line;
};


#endif //MONTADOR_PARSINGEXCEPTION_H
