//
// Created by mateusberardo on 08/03/2021.
//

#include <parsingerrors/unknownoperationerror.h>
#include <exceptions/operationnotfoundexception.h>
#include <parsingerrors/invalidoperandcounterror.h>
#include "datafirstpasser.h"


DataFirstPasser::DataFirstPasser(std::string fileContent, SymbolTable *st,
                                 uint16_t startingAddress, long startingLine)
        : fileContent(std::move(fileContent)), symbolTable(st),
          startingAddress(startingAddress), nowLine(startingLine){
}

std::vector<DataLine> DataFirstPasser::getDataLines() {
    return dataLines;
}

void DataFirstPasser::pass() {
    size_t initPos = 0;
    uint16_t nowAddress = startingAddress;
    while (true){
        auto nextPos = getLineEnd(initPos);
        auto line = getLine(initPos, nextPos);

        try {
            DataLine dataLine = DataLine(line);
            if (!dataLine.isValid())
                errors.insert(errors.end(),
                              InvalidOperandCountError(nowLine, dataLine.getOperationMnemonic()));
            addDataLine(dataLine);

            updateSymbolTable(nowAddress, dataLine);

            nowAddress+=dataLine.getAddressSize();


        } catch (OperationNotFoundException &exception) {
            errors.insert(errors.end(),
                          UnknownOperationError(nowLine, exception.what()));
        }
        if (nextPos == std::string::npos)
            break;
        initPos = nextPos + 1;
        nowLine++;
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

std::vector<ParsingError> DataFirstPasser::getErrors() {
    return errors;
}

int16_t DataFirstPasser::getErrorCount() {
    return errors.size();
}
