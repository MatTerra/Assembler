//
// Created by mateusberardo on 08/03/2021.
//

#ifndef MONTADOR_DATAFIRSTPASSER_H
#define MONTADOR_DATAFIRSTPASSER_H

#include <string>
#include <utility>
#include <vector>
#include "symboltable.h"
#include "dataline.h"
#include "parsingerrors/parsingerror.h"

class DataFirstPasser {
public:
    explicit DataFirstPasser(std::string fileContent, SymbolTable *st,
                             uint16_t startingAddress=0, long startingLine=1);
    size_t getSymbolCount() { return symbolTable->getSymbolCount(); }
    SymbolTable *getSymbolTable() { return symbolTable; }
    std::vector<DataLine> getDataLines();

    void pass();

    std::vector<ParsingError> getErrors();

    int16_t getErrorCount();

private:
    std::string fileContent;
    SymbolTable *symbolTable;
    std::vector<DataLine> dataLines;

    void addDataLine(const DataLine &dataLine);
    unsigned long getLineEnd(size_t initPos) const;
    std::string getLine(size_t initPos, unsigned long nextPos) const;
    void updateSymbolTable(DataLine &dataLine);

    uint16_t nowAddress;
    std::vector<ParsingError> errors;
    long nowLine;

    void processLine(std::string line);

    void updateAddress(DataLine &dataLine);

    void validateOperation(DataLine &dataLine);
};


#endif //MONTADOR_DATAFIRSTPASSER_H
