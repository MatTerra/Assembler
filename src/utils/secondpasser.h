//
// Created by mateusberardo on 05/03/2021.
//

#ifndef MONTADOR_SECONDPASSER_H
#define MONTADOR_SECONDPASSER_H


#include <utility>
#include <vector>
#include <string>
#include "codeline.h"
#include "symboltable.h"

class SecondPasser {
public:
    SecondPasser(std::vector<CodeLine> codeLines, SymbolTable* symbolTable,
                 uint16_t startingLine = 1)
        :codeLines(std::move(codeLines)), symbolTable(symbolTable),
         startingLine(startingLine){};

    void pass();

    std::string getProcessedLine(int line);

    std::vector<ParsingException> getErrors();

private:
    uint16_t startingLine;
    std::vector<CodeLine> codeLines;
    SymbolTable *symbolTable;
    std::vector<std::string> processedLines;
    std::vector<ParsingException> errors;
    std::ostringstream processedLine;

    void addOpCodeToProcessedLine(CodeLine &line);

    void addOperandsAddressesToProcessedLine(CodeLine &line);

    void addFormattedOperandToProcessedLine(std::string &operand);

    void processOperation(CodeLine &line);

    void processLine(CodeLine &line, uint16_t lineNumber);

    void validateOperation(CodeLine &line) const;
};


#endif //MONTADOR_SECONDPASSER_H
