//
// Created by mateusberardo on 01/03/2021.
//

#ifndef MONTADOR_CODEFIRSTPASSER_H
#define MONTADOR_CODEFIRSTPASSER_H

#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <utility>
#include <exceptions/symbolalreadyexistsexception.h>
#include <parsingerrors/symbolredefinederror.h>
#include <parsingerrors/parsingerror.h>
#include <symboltable.h>
#include <codeline.h>

class CodeFirstPasser {
public:
    explicit CodeFirstPasser(std::string fileContent, uint64_t startingLine=1,
                             SymbolTable *st= nullptr);
    size_t getSymbolCount() { return symbolTable->getSymbolCount(); }
    SymbolTable *getSymbolTable() { return symbolTable; }
    std::vector<CodeLine> getCodeLines();

    void pass();

    uint16_t getFinalAddress() const;

    int getErrorCount();

    std::vector<ParsingError> getErrors();

private:
    std::string fileContent;
    SymbolTable *symbolTable;
    std::vector<CodeLine> codeLines;

    void addCodeLine(const CodeLine &codeLine);
    void updateSymbolTable(CodeLine &codeLine);

    uint16_t nowAddress{};
    std::vector<ParsingError> errors;

    void updateAddress(CodeLine &codeLine);

    void processLine(std::string line);

    uint64_t nowLine;

    bool isExternSymbol(CodeLine &codeLine) const;

    bool isExtern(CodeLine &codeLine) const;
};


#endif //MONTADOR_CODEFIRSTPASSER_H
