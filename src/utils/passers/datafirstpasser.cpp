//
// Created by mateusberardo on 08/03/2021.
//

#include <parsingerrors/unknownoperationerror.h>
#include <exceptions/operationnotfoundexception.h>
#include <parsingerrors/invalidoperandcounterror.h>
#include <exceptions/symbolalreadyexistsexception.h>
#include <parsingerrors/symbolredefinederror.h>

#include <utility>
#include <parsingerrors/invalidoperanderror.h>
#include "datafirstpasser.h"


DataFirstPasser::DataFirstPasser(std::string fileContent, SymbolTable *st,
                                 uint16_t startingAddress, long startingLine)
        : fileContent(std::move(fileContent)), symbolTable(st),
          nowAddress(startingAddress), nowLine(startingLine){
}

std::vector<DataLine> DataFirstPasser::getDataLines() {
    return dataLines;
}

void DataFirstPasser::pass() {
    size_t initPos = 0;
    while (true){
        auto nextPos = getLineEnd(initPos);

        processLine(getLine(initPos, nextPos));
        nowLine++;

        if (nextPos == std::string::npos)
            break;
        initPos = nextPos + 1;
    }
}

void DataFirstPasser::processLine(std::string line) {
    auto dataLine = DataLine(std::move(line));

    validateOperation(dataLine);

    addDataLine(dataLine);

    updateSymbolTable(dataLine);

    updateAddress(dataLine);
}

void DataFirstPasser::validateOperation(DataLine &dataLine) {
    if (!dataLine.isValid()) {
        if (dataLine.getOperation() == nullptr && dataLine.hasOperation()) {
            errors.insert(errors.end(), InvalidOperandError(nowLine, dataLine.getOperands()[0]));
            return;
        }
        errors.insert(errors.end(), InvalidOperandCountError(nowLine, dataLine.getOperationMnemonic()));
        return;
    }
    if(dataLine.hasOperation() && dataLine.getOperation() == nullptr)
        errors.insert(errors.end(),
                      UnknownOperationError(nowLine, dataLine.getOperationMnemonic()));
}

void DataFirstPasser::updateSymbolTable(DataLine &dataLine) {
    if (dataLine.hasLabel())
        try {
            symbolTable->addSymbol(dataLine.getLabel(), nowAddress);
        }catch (SymbolAlreadyExistsException &exception){
            errors.insert(errors.end(), SymbolRedefinedError(nowLine,
                                                             exception.what()));
        }
}

void DataFirstPasser::updateAddress(DataLine &dataLine) {
    nowAddress += dataLine.getAddressSize();
    for (int i= dataLine.getAddressSize(); i>0;i--)
        relocationBitmap.insert(relocationBitmap.end(), '0');
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

uint16_t DataFirstPasser::getFinalAddress() {
    return nowAddress;
}

std::string DataFirstPasser::getRelocationBitmap() {
    return relocationBitmap;
}
