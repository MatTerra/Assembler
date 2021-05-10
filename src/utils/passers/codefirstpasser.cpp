//
// Created by mateusberardo on 01/03/2021.
//

#include <parsingerrors/invalidlabelerror.h>
#include <parsingerrors/missinglabelerror.h>
#include <exceptions/symbolinvalidexception.h>
#include "codefirstpasser.h"

CodeFirstPasser::CodeFirstPasser(std::string fileContent,
                                 uint64_t startingLine, SymbolTable *st)
        : fileContent(std::move(fileContent)),
          nowAddress(0), nowLine(startingLine){
    if (st == nullptr)
        symbolTable = new SymbolTable();
}

std::vector<CodeLine> CodeFirstPasser::getCodeLines() {
    return codeLines;
}

void CodeFirstPasser::pass() {
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


void CodeFirstPasser::processLine(std::string line) {
    auto codeLine = CodeLine(std::move(line));

    addCodeLine(codeLine);

    updateSymbolTable(codeLine);

    updateAddress(codeLine);
}

void CodeFirstPasser::addCodeLine(const CodeLine &codeLine) {
    codeLines.insert(codeLines.cend(), codeLine);
}

void CodeFirstPasser::updateSymbolTable(CodeLine &codeLine) {
    if (codeLine.hasLabel())
        try {
            symbolTable->addSymbol(codeLine.getLabel(), nowAddress,
                                   isExternSymbol(codeLine));
        } catch (SymbolAlreadyExistsException &exception) {
            errors.insert(errors.end(), SymbolRedefinedError(nowLine,
                                                             exception.what()));

        } catch (SymbolInvalidException &exception){
            errors.insert(errors.end(), InvalidLabelError(nowLine,
                                                          exception.what()));
        }
    else if (isExtern(codeLine))
        errors.insert(errors.end(), MissingLabelError(nowLine));
}

bool CodeFirstPasser::isExtern(CodeLine &codeLine) const {
    if(codeLine.getOperation() == nullptr)
        return false;
    return codeLine.getOperation()->getOpCode() == 0
        && codeLine.getOperation()->getOperation() == "extern";
}

bool CodeFirstPasser::isExternSymbol(CodeLine &codeLine) const {
    if (codeLine.hasOperation())
        return codeLine.getOperation()->getOpCode() == 0;
    return false;
}

void CodeFirstPasser::updateAddress(CodeLine &codeLine) {
    nowAddress += codeLine.getAddressSize();
}

uint16_t CodeFirstPasser::getFinalAddress() const {
    return nowAddress;
}

int CodeFirstPasser::getErrorCount() {
    return errors.size();
}

std::vector<ParsingError> CodeFirstPasser::getErrors() {
    return errors;
}



