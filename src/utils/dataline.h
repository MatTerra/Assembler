//
// Created by mateusberardo on 08/03/2021.
//

#ifndef MONTADOR_DATALINE_H
#define MONTADOR_DATALINE_H


#include <utility>

#include "processedline.h"
#include "datatype.h"

class DataLine : public ProcessedLine {
public:
    explicit DataLine(std::string line);
    bool operator==(DataLine other) const;
    uint16_t getAddressSize() override { return hasOperation() ? 1 : 0; }

    int16_t getValue();

    bool isValid();

private:
    DataType *operation;
    void extractOperation() override;;
};


#endif //MONTADOR_DATALINE_H
