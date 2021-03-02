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
    while (true){
        auto nextPos = fileContent.find_first_of('\n', initPos+1);
        auto line = fileContent.substr(initPos, (nextPos)-initPos);
        const CodeLine &codeLine = CodeLine(line);
        codeLines.insert(codeLines.cend(), codeLine);
        if (nextPos == std::string::npos)
            break;
        initPos = ++nextPos;
    }
}
