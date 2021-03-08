//
// Created by mateusberardo on 01/03/2021.
//

#include <iostream>
#include "codefirstpasser.h"

CodeFirstPasser::CodeFirstPasser(std::string fileContent)
        :fileContent(std::move(fileContent)){
    symbolTable = new SymbolTable();
}

std::vector<CodeLine> CodeFirstPasser::getCodeLines() {
    return codeLines;
}

void CodeFirstPasser::pass() {
    size_t initPos = 0;
    uint16_t nowAddress = 0;
    while (true){
        auto nextPos = getLineEnd(initPos);
        auto line = getLine(initPos, nextPos);

        CodeLine codeLine = CodeLine(line);
        addCodeLine(codeLine);

        updateSymbolTable(nowAddress, codeLine);

        nowAddress+=codeLine.getAddressSize();

        if (nextPos == std::string::npos)
            break;
        initPos = nextPos + 1;
    }
}

void CodeFirstPasser::updateSymbolTable(uint16_t nowAddress, CodeLine &codeLine) {
    if (codeLine.hasLabel())
        symbolTable->addSymbol(codeLine.getLabel(), nowAddress);
}

std::string CodeFirstPasser::getLine(size_t initPos, unsigned long nextPos) const {
    return fileContent.substr(initPos, (nextPos) - initPos);
}

unsigned long CodeFirstPasser::getLineEnd(size_t initPos) const {
    return fileContent.find_first_of('\n', initPos + 1);
}

void CodeFirstPasser::addCodeLine(const CodeLine &codeLine) {
    codeLines.insert(codeLines.cend(), codeLine);
}
