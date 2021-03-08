//
// Created by mateusberardo on 08/03/2021.
//

#ifndef MONTADOR_CONSTDATATYPE_H
#define MONTADOR_CONSTDATATYPE_H


#include <string>
#include <datatype.h>

class ConstDataType : public DataType {
public:
    ConstDataType(std::string symbol, std::string value);

};


#endif //MONTADOR_SPACEDATATYPE_H
