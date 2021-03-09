//
// Created by mateusberardo on 05/03/2021.
//
#include <iomanip>
#include <sstream>
#include <exceptions/undefinedsymbolexception.h>
#include <exceptions/symbolnotfoundexception.h>
#include <exceptions/operationnotfoundexception.h>
#include <exceptions/unknownoperationexception.h>
#include <exceptions/invalidoperandcountexception.h>
#include <exceptions/invalidoperationexception.h>
#include "secondpasser.h"

std::string SecondPasser::getProcessedLine(int line) {
    if (line >= getLineCount())
        return "";
    return processedLines[line];
}

void SecondPasser::pass() {
    uint16_t lineCounter = startingLine;
    for (auto &line : codeLines)
        processLine(line, lineCounter++);
}

void SecondPasser::processLine(CodeLine &line, uint16_t lineNumber) {
    std::ostringstream processedLine;

    if (line.hasOperation())
        processOperation(line, processedLine, lineNumber);

    processedLines.insert(processedLines.end(),
                          processedLine.str());
}

void SecondPasser::processOperation(CodeLine &line,
                                    std::ostringstream &processedLine,
                                    long lineNumber) {
    validateOperation(line, lineNumber);
    addOpCodeToProcessedLine(line, processedLine);
    addOperandsAddressesToProcessedLine(line, processedLine, lineNumber);
}

void SecondPasser::validateOperation(CodeLine &line, long lineNumber) {
    if (line.getOperation() == nullptr) {
        errors.insert(errors.end(), UnknownOperationException(lineNumber, line.getOperationMnemonic()));
        return;
    }
    if (!line.getOperation()->isValid())
        errors.insert(errors.end(), InvalidOperandCountException(lineNumber, line.getOperationMnemonic()));
}

void SecondPasser::addOpCodeToProcessedLine(CodeLine &line,
                                            std::ostringstream &processedLine) {
    processedLine << std::setfill('0') << std::setw(2) << line.getOpCode();
}

void SecondPasser::addOperandsAddressesToProcessedLine(CodeLine &line,
                                                       std::ostringstream &processedLine,
                                                       long lineNumber) {
    for (auto &operand : line.getOperands())
        addFormattedOperandToProcessedLine(operand, processedLine, lineNumber);
}

void SecondPasser::addFormattedOperandToProcessedLine(std::string &operand,
                                                      std::ostringstream &processedLine,
                                                      long lineNumber) {
    try{
        processedLine << " " << std::setfill('0')
                      << std::setw(2)
                      << symbolTable->getSymbolAddress(operand);
    }  catch (SymbolNotFoundException &exception) {
        errors.insert(errors.end(),
                      UndefinedSymbolException(lineNumber, operand));
    }
}

std::vector<ParsingException> SecondPasser::getErrors() {
    return errors;
}

int16_t SecondPasser::getErrorCount() {
    return errors.size();
}

uint16_t SecondPasser::getLineCount() {
    return processedLines.size();
}
