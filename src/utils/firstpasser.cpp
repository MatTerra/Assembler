//
// Created by mateusberardo on 01/03/2021.
//

#include <iostream>
#include "firstpasser.h"

FirstPasser::FirstPasser(std::string fileContent)
        :fileContent(std::move(fileContent)){
    symbolTable = SymbolTable::getInstance();
}

std::vector<CodeLine> FirstPasser::getCodeLines() {
    return codeLines;
}

void FirstPasser::pass() {
    size_t initPos = 0;
    uint16_t nowAddress = 0;
    while (true){
        auto nextPos = getLineEnd(initPos);

        CodeLine codeLine = CodeLine(getLine(initPos, nextPos));
        addCodeLine(codeLine);

        updateSymbolTable(nowAddress, codeLine);

        nowAddress+=codeLine.getAddressSize();

        if (nextPos == std::string::npos)
            break;
        initPos = nextPos + 1;
    }
}

void FirstPasser::updateSymbolTable(uint16_t nowAddress, CodeLine &codeLine) {
    if (codeLine.hasLabel())
        symbolTable->addSymbol(codeLine.getLabel(), nowAddress);
}

std::string FirstPasser::getLine(size_t initPos,
                                 unsigned long nextPos) const { return fileContent.substr(initPos, (nextPos) - initPos); }

unsigned long FirstPasser::getLineEnd(
        size_t initPos) const { return fileContent.find_first_of('\n', initPos + 1); }

void FirstPasser::addCodeLine(const CodeLine &codeLine) {
    codeLines.insert(codeLines.cend(), codeLine);
}
