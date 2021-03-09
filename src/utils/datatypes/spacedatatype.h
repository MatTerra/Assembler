//
// Created by mateusberardo on 08/03/2021.
//

#ifndef MONTADOR_SPACEDATATYPE_H
#define MONTADOR_SPACEDATATYPE_H


#include <string>
#include <datatype.h>

class SpaceDataType : public DataType {
public:
    SpaceDataType(std::string symbol);
    uint8_t getRequiredOperandCount() override { return 0; }

};


#endif //MONTADOR_SPACEDATATYPE_H
