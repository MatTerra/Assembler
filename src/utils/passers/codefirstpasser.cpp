//
// Created by mateusberardo on 01/03/2021.
//

#include <parsingerrors/invalidlabelerror.h>
#include <parsingerrors/missinglabelerror.h>
#include "codefirstpasser.h"

CodeFirstPasser::CodeFirstPasser(std::string fileContent, uint64_t startingLine)
        : fileContent(std::move(fileContent)),
          nowAddress(0), nowLine(startingLine){
    symbolTable = new SymbolTable();
}

std::vector<CodeLine> CodeFirstPasser::getCodeLines() {
    return codeLines;
}

void CodeFirstPasser::pass() {
    size_t lineStart = 0;
    while (true){
        auto lineEnd = getLineEnd(lineStart);

        processLine(getLine(lineStart, lineEnd));
        nowLine++;

        if (!hasMoreLines(lineEnd))
            break;
        lineStart = ++lineEnd;
    }
}

unsigned long CodeFirstPasser::getLineEnd(size_t initPos) const {
    return fileContent.find_first_of('\n', initPos);
}

std::string CodeFirstPasser::getLine(size_t initPos, unsigned long nextPos) const {
    return fileContent.substr(initPos, (nextPos) - initPos);
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
            if (!SymbolTable::isValidSymbol(codeLine.getLabel())) {
                errors.insert(errors.end(), InvalidLabelError(nowLine,
                                                              codeLine.getLabel()));
                return;
            }
            symbolTable->addSymbol(codeLine.getLabel(), nowAddress,
                                   isExternSymbol(codeLine));
        } catch (SymbolAlreadyExistsException &exception) {
            errors.insert(errors.end(), SymbolRedefinedError(nowLine,
                                                             exception.what()));

        }
    else if (codeLine.getOperation() != nullptr)
        if (codeLine.getOperation()->getOpCode() == 0)
            errors.insert(errors.end(), MissingLabelError(nowLine));
}

bool CodeFirstPasser::isExternSymbol(CodeLine &codeLine) const {
    if (codeLine.hasOperation())
        return codeLine.getOperation()->getOpCode() == 0;
    return false;
}

void CodeFirstPasser::updateAddress(CodeLine &codeLine) {
    nowAddress += codeLine.getAddressSize();
}

bool CodeFirstPasser::hasMoreLines(unsigned long lineEnd) const {
    return lineEnd != std::string::npos;
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



