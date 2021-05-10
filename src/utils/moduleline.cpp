//
// Created by mateusberardo on 26/02/2021.
//
#include <iostream>
#include <vector>
#include "moduleline.h"
#include "baseoperationfactory.h"

ModuleLine::ModuleLine(std::string line) :ProcessedLine(std::move(line)){
    if (hasOperation())
        extractOperation();
    else
        operation = nullptr;
}

void ModuleLine::extractOperation() {
    auto operationFactory = getModuleOperationFactory();
    operation = operationFactory->create(operationMnemonic, operands);
}

bool ModuleLine::operator==(const ModuleLine other) const {
    return getRawLine() == other.getRawLine();
}


uint16_t ModuleLine::getAddressSize() {
    if (operation == nullptr)
        return 0;
    return operation->getAddressSize();
}

std::string ModuleLine::getOpCode() {
    if (operation != nullptr)
        return std::to_string(operation->getOpCode());
    return "";
}

