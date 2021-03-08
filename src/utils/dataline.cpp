//
// Created by mateusberardo on 08/03/2021.
//

#include <algorithm>
#include <exceptions/operationnotfoundexception.h>
#include "dataline.h"
#include "datatypes/spacedatatype.h"
#include "datatypes/constdatatype.h"

DataLine::DataLine(std::string line) : ProcessedLine(std::move(line)) {
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
    if (operationMnemonic == "const") {
        operation = new ConstDataType(getLabel(), getOperands()[0]);
    } else if (operationMnemonic == "space"){
        operation = new SpaceDataType(getLabel());
    } else {
        throw OperationNotFoundException(operationMnemonic);
    }
}

int16_t DataLine::getValue() {
    if (operation == nullptr)
        return 0;
    return operation->getValue();
}
