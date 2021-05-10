//
// Created by mateusberardo on 10/05/2021.
//

#ifndef MONTADOR_MODULEPASSER_H
#define MONTADOR_MODULEPASSER_H

#include <string>
#include <vector>
#include <parsingerrors/parsingerror.h>
#include <symboltable.h>
#include <moduleline.h>


class ModulePasser {
public:
    explicit ModulePasser(std::string fileContent, uint64_t startingLine=0,
                          SymbolTable* st=nullptr);

    void pass();

    std::vector<ParsingError> getErrors();

    SymbolTable *getSymbolTable();

private:
    std::string fileContent;
    SymbolTable *symbolTable;
    uint64_t nowLine;

    void processLine(std::string line);

    void updateSymbolTable(ModuleLine moduleLine);

    bool isExternSymbol(ModuleLine moduleLine);

    std::vector<ParsingError> errors;

    bool isExtern(ModuleLine moduleLine);

    bool isPublic(ModuleLine moduleLine);
};


#endif //MONTADOR_MODULEPASSER_H
