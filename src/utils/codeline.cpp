//
// Created by mateusberardo on 26/02/2021.
//
#include <iostream>
#include <vector>
#include "codeline.h"
#include "baseoperationfactory.h"

CodeLine::CodeLine(std::string line) :ProcessedLine(std::move(line)){
    if (hasOperation())
        extractOperation();
    else
        operation = nullptr;
}

void CodeLine::extractOperation() {
    auto operationFactory = getBaseOperationFactory();
    operation = operationFactory->create(operationMnemonic, operands);
}

bool CodeLine::operator==(const CodeLine other) const {
    return getRawLine() == other.getRawLine();
}


uint16_t CodeLine::getAddressSize() {
    if (operation == nullptr)
        return 0;
    return operation->getAddressSize();
}

std::string CodeLine::getOpCode() {
    if (operation != nullptr)
        return std::to_string(operation->getOpCode());
    return "";
}

