//
// Created by mateusberardo on 01/03/2021.
//

#ifndef MONTADOR_CODEFIRSTPASSER_H
#define MONTADOR_CODEFIRSTPASSER_H

#include <string>
#include <utility>
#include <vector>
#include "symboltable.h"
#include "codeline.h"

class CodeFirstPasser {
public:
    explicit CodeFirstPasser(std::string fileContent);
    size_t getSymbolCount() { return symbolTable->getSymbolCount(); }
    SymbolTable *getSymbolTable() { return symbolTable; }
    std::vector<CodeLine> getCodeLines();

    void pass();

    uint16_t getFinalAddress() const;

private:
    std::string fileContent;
    SymbolTable *symbolTable;
    std::vector<CodeLine> codeLines;

    void addCodeLine(const CodeLine &codeLine);
    unsigned long getLineEnd(size_t initPos) const;
    std::string getLine(size_t initPos, unsigned long nextPos) const;
    void updateSymbolTable(CodeLine &codeLine);

    uint16_t nowAddress{};
};


#endif //MONTADOR_CODEFIRSTPASSER_H
