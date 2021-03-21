//
// Created by mateusberardo on 08/03/2021.
//

#include <algorithm>
#include <exceptions/operationnotfoundexception.h>
#include "dataline.h"
#include "datatypes/spacedatatype.h"
#include "datatypes/constdatatype.h"

DataLine::DataLine(std::string line)
        : ProcessedLine(std::move(line)), operation(nullptr),
        operandsValid(true) {
    if (hasOperation())
        extractOperation();
}

bool DataLine::operator==(const DataLine other) const {
    return getRawLine() == other.getRawLine();
}

void DataLine::extractOperation() {
    std::transform(operationMnemonic.begin(), operationMnemonic.end(),
                   operationMnemonic.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    operation = nullptr;
    createOperation();
}

void DataLine::createOperation() {
    try {
        if (operationMnemonic == "const") {
            if (operands.size() == 1)
                operation = new ConstDataType(getLabel(), getOperands()[0]);
            else
                operation = new ConstDataType(getLabel(), "0");
        } else if (operationMnemonic == "space") {
            operation = new SpaceDataType(getLabel());
        }
    } catch (std::invalid_argument) {
        operandsValid = false;
    }
}

int16_t DataLine::getValue() {
    if (operation == nullptr)
        return 0;
    return operation->getValue();
}

bool DataLine::isValid() {
    if (!operandsValid)
        return false;
    if (operation == nullptr)
        return true;
    return operands.size() == operation->getRequiredOperandCount();
}

DataType *DataLine::getOperation() {
    return operation;
}
