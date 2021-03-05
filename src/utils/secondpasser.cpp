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
    return processedLines[line];
}

void SecondPasser::pass() {
    uint16_t lineCounter = startingLine;
    for (auto &line : codeLines)
        processLine(line, lineCounter++);
}

void SecondPasser::processLine(CodeLine &line, uint16_t lineNumber) {
    try {
        processedLine.clear();

        if (line.hasOperation())
            processOperation(line);

        processedLines.insert(processedLines.cend(),
                              processedLine.str());
    } catch (SymbolNotFoundException &exception) {
        errors.insert(errors.cend(),
                      UndefinedSymbolException(lineNumber, exception.what()));
    } catch (OperationNotFoundException &exception){
        errors.insert(errors.cend(),
                      UnknownOperationException(lineNumber, exception.what()));
    } catch (std::runtime_error &exception){
        errors.insert(errors.cend(),
                      InvalidOperandCountException(lineNumber,
                                                   exception.what()));
    }
}

void SecondPasser::processOperation(CodeLine &line) {
    validateOperation(line);
    addOpCodeToProcessedLine(line);
    addOperandsAddressesToProcessedLine(line);
}

void SecondPasser::validateOperation(CodeLine &line) const {
    if (line.getOperation() == nullptr)
        throw OperationNotFoundException(line.getOperationMnemonic());
    if (!line.getOperation()->isValid())
        throw InvalidOperationException(line.getOperationMnemonic());
}

void SecondPasser::addOpCodeToProcessedLine(CodeLine &line) {
    processedLine << std::setfill('0') << std::setw(2) << line.getOpCode();
}

void SecondPasser::addOperandsAddressesToProcessedLine(CodeLine &line) {
    for (auto &operand : line.getOperands())
        addFormattedOperandToProcessedLine(operand);
}

void SecondPasser::addFormattedOperandToProcessedLine(std::string &operand) {
    processedLine << " " << std::setfill('0')
                  << std::setw(2) << symbolTable->getSymbolAddress(operand);
}

std::vector<ParsingException> SecondPasser::getErrors() {
    return errors;
}
