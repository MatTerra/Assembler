//
// Created by mateusberardo on 10/05/2021.
//

#include <moduleline.h>
#include <parsingerrors/symbolredefinederror.h>
#include <parsingerrors/invalidlabelerror.h>
#include <parsingerrors/missinglabelerror.h>
#include <parsingerrors/invalidoperandcounterror.h>
#include "modulepasser.h"

ModulePasser::ModulePasser(std::string fileContent,
                           uint64_t startingLine, SymbolTable* st)
        : fileContent(fileContent), nowLine(startingLine), symbolTable(st) {
    if (symbolTable == nullptr)
        symbolTable = new SymbolTable();
}

void ModulePasser::pass() {
    size_t lineStart = 0;
    while (true){
        auto lineEnd = getLineEnd(fileContent, lineStart);

        processLine(getLine(fileContent, lineStart, lineEnd));
        nowLine++;

        if (!hasMoreLines(lineEnd))
            break;
        lineStart = ++lineEnd;
    }
}

SymbolTable *ModulePasser::getSymbolTable() {
    return symbolTable;
}

void ModulePasser::processLine(std::string line) {
    auto moduleLine = ModuleLine(std::move(line));

    updateSymbolTable(moduleLine);
}

void ModulePasser::updateSymbolTable(ModuleLine moduleLine) {
    if (moduleLine.hasLabel())
        try {
            symbolTable->addSymbol(moduleLine.getLabel(), 0,
                                   isExternSymbol(moduleLine));
        } catch (SymbolAlreadyExistsException &exception) {
            errors.insert(errors.end(), SymbolRedefinedError(nowLine,
                                                             exception.what()));

        }
    else if (isExtern(moduleLine))
        errors.insert(errors.end(), MissingLabelError(nowLine));
    else if (isPublic(moduleLine)){
//        if (moduleLine.getOperands().size() < 1)
//            errors.insert(errors.end(), InvalidOperandCountError(nowLine,
//                                                                 "public"));
        for (auto operand : moduleLine.getOperands()) {
            symbolTable->setPublicSymbol(operand);
        }
    }
}

bool ModulePasser::isExternSymbol(ModuleLine moduleLine) {
    if (moduleLine.hasOperation())
        return moduleLine.getOperation()->getOpCode() == 0;
    return false;
}

bool ModulePasser::isExtern(ModuleLine moduleLine) {
    if(moduleLine.getOperation() == nullptr)
        return false;
    return moduleLine.getOperation()->getOpCode() == 0
           && moduleLine.getOperation()->getOperation() == "extern";
}

std::vector<ParsingError> ModulePasser::getErrors() {
    return errors;
}

bool ModulePasser::isPublic(ModuleLine moduleLine) {
    if(moduleLine.getOperation() == nullptr)
        return false;
    return moduleLine.getOperation()->getOpCode() == 0
           && moduleLine.getOperation()->getOperation() == "public";
}
