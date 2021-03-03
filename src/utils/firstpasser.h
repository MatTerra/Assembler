//
// Created by mateusberardo on 01/03/2021.
//

#ifndef MONTADOR_FIRSTPASSER_H
#define MONTADOR_FIRSTPASSER_H

#include <string>
#include <utility>
#include <vector>
#include "symboltable.h"
#include "codeline.h"

class FirstPasser {
public:
    explicit FirstPasser(std::string fileContent);
    size_t getSymbolCount() { return symbolTable->getSymbolCount(); }
    SymbolTable *getSymbolTable() { return symbolTable; }
    std::vector<CodeLine> getCodeLines();

    void pass();

private:
    std::string fileContent;
    SymbolTable *symbolTable;
    std::vector<CodeLine> codeLines;

    void addCodeLine(const CodeLine &codeLine);
    unsigned long getLineEnd(size_t initPos) const;
    std::string getLine(size_t initPos, unsigned long nextPos) const;
    void updateSymbolTable(uint16_t nowAddress, CodeLine &codeLine);
};


#endif //MONTADOR_FIRSTPASSER_H
