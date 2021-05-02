//
// Created by mateusberardo on 05/03/2021.
//
#include <iomanip>
#include <sstream>
#include <parsingerrors/undefinedsymbolerror.h>
#include <exceptions/symbolnotfoundexception.h>
#include <parsingerrors/unknownoperationerror.h>
#include <parsingerrors/invalidoperandcounterror.h>
#include <parsingerrors/invalidoperanderror.h>
#include <usetable.h>
#include "secondpasser.h"

std::string SecondPasser::getProcessedLine(int line) {
    if (line >= getLineCount())
        return "";
    return processedLines[line];
}

void SecondPasser::pass() {
    for (auto &line : codeLines)
        processLine(line);
}

void SecondPasser::processLine(CodeLine &line) {
    std::ostringstream processedLine;

    if (line.hasOperation())
        processOperation(line, processedLine);

    nowLine++;
}

void SecondPasser::processOperation(CodeLine &line,
                                    std::ostringstream &processedLine) {
    validateOperation(line);
    if (line.getOpCode() != "0") {
        addOpCodeToProcessedLine(line, processedLine);
        addOperandsAddressesToProcessedLine(line, processedLine);
        processedLines.insert(processedLines.end(),
                              processedLine.str());
    } else if (line.getOperation()->getOperation() == "public"){
        symbolTable->setPublicSymbol(line.getOperands()[0]);
    }
}

void SecondPasser::validateOperation(CodeLine &line) {
    if (line.getOperation() == nullptr) {
        errors.insert(errors.end(), UnknownOperationError(nowLine, line.getOperationMnemonic()));
        return;
    }
    if (!line.getOperation()->isValid())
        errors.insert(errors.end(), InvalidOperandCountError(nowLine, line.getOperationMnemonic()));
}

void SecondPasser::addOpCodeToProcessedLine(CodeLine &line,
                                            std::ostringstream &processedLine) {
    processedLine << std::setfill('0') << std::setw(2) << line.getOpCode();
    relocationBitmap.insert(relocationBitmap.end(), '0');
}

void SecondPasser::addOperandsAddressesToProcessedLine(CodeLine &line,
                                                       std::ostringstream &processedLine) {
    for (auto &operand : line.getOperands())
        addFormattedOperandToProcessedLineIfValid(operand, processedLine);
}

void
SecondPasser::addFormattedOperandToProcessedLineIfValid(std::string &operand,
                                                        std::ostringstream &processedLine) {
    try{
        if (SymbolTable::isValidSymbol(operand)) {
            processedLine << " " << std::setfill('0')
                          << std::setw(2)
                          << symbolTable->getSymbolAddress(operand);
            if (symbolTable->isExternSymbol(operand))
                useTable->addSymbolUse(operand, relocationBitmap.length());
            relocationBitmap.insert(relocationBitmap.end(), '1');
            return;
        }
        errors.insert(errors.end(), InvalidOperandError(nowLine, operand));
    }  catch (SymbolNotFoundException &exception) {
        errors.insert(errors.end(),
                      UndefinedSymbolError(nowLine, operand));
    }
}

std::vector<ParsingError> SecondPasser::getErrors() {
    return errors;
}

int16_t SecondPasser::getErrorCount() {
    return errors.size();
}

uint16_t SecondPasser::getLineCount() {
    return processedLines.size();
}

std::vector<std::string> SecondPasser::getProcessedLines() {
    return processedLines;
}

std::string SecondPasser::getRelocationBitmap() {
    return relocationBitmap;
}

UseTable *SecondPasser::getUseTable() {
    return useTable;
}
