//
// Created by mateusberardo on 08/03/2021.
//

#ifndef MONTADOR_DATATYPE_H
#define MONTADOR_DATATYPE_H

#include <string>
#include <utility>

class DataType{
public:
    DataType(std::string symbol, std::string value)
        : symbol(std::move(symbol)), value(std::stoi(value)){};
    DataType(std::string symbol, uint16_t value)
            : symbol(std::move(symbol)), value(value){};
    std::string getSymbol(){ return symbol; }
    int16_t getValue() const{ return value; }
protected:
    std::string symbol;
    int16_t value;
};

#endif //MONTADOR_DATATYPE_H
