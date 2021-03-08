//
// Created by mateusberardo on 08/03/2021.
//

#include <iostream>
#include "datafirstpasser.h"

DataFirstPasser::DataFirstPasser(std::string fileContent, SymbolTable *st)
        :fileContent(std::move(fileContent)), symbolTable(st){
}

std::vector<DataLine> DataFirstPasser::getDataLines() {
    return dataLines;
}

void DataFirstPasser::pass() {
    size_t initPos = 0;
    uint16_t nowAddress = 0;
    while (true){
        auto nextPos = getLineEnd(initPos);
        auto line = getLine(initPos, nextPos);

        DataLine dataLine = DataLine(line);
        addDataLine(dataLine);

        updateSymbolTable(nowAddress, dataLine);

        nowAddress+=dataLine.getAddressSize();

        if (nextPos == std::string::npos)
            break;
        initPos = nextPos + 1;
    }
}

void DataFirstPasser::updateSymbolTable(uint16_t nowAddress, DataLine &dataLine) {
    if (dataLine.hasLabel())
        symbolTable->addSymbol(dataLine.getLabel(), nowAddress);
}

std::string DataFirstPasser::getLine(size_t initPos, unsigned long nextPos) const {
    return fileContent.substr(initPos, (nextPos) - initPos);
}

unsigned long DataFirstPasser::getLineEnd(size_t initPos) const {
    return fileContent.find_first_of('\n', initPos + 1);
}

void DataFirstPasser::addDataLine(const DataLine &dataLine) {
    dataLines.insert(dataLines.cend(), dataLine);
}
