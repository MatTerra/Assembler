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
#include "parsingerrors/parsingerror.h"

class SecondPasser {
public:
    SecondPasser(std::vector<CodeLine> codeLines, SymbolTable* symbolTable,
                 uint64_t startingLine = 1)
        :codeLines(std::move(codeLines)), symbolTable(symbolTable),
         startingLine(startingLine){};

    void pass();

    std::string getProcessedLine(int line);
    std::vector<ParsingError> getErrors();

    int16_t getErrorCount();

    uint16_t getLineCount();

private:
    uint16_t startingLine;
    std::vector<CodeLine> codeLines;
    SymbolTable *symbolTable;
    std::vector<std::string> processedLines;
    std::vector<ParsingError> errors;

    void
    addOpCodeToProcessedLine(CodeLine &line, std::ostringstream &processedLine);
    void addOperandsAddressesToProcessedLine(CodeLine &line,
                                             std::ostringstream &processedLine,
                                             uint64_t lineNumber);
    void addFormattedOperandToProcessedLine(std::string &operand,
                                            std::ostringstream &processedLine,
                                            uint64_t lineNumber);
    void processOperation(CodeLine &line,
                          std::ostringstream &processedLine,
                          long lineNumber);
    void processLine(CodeLine &line, uint64_t lineNumber);
    void validateOperation(CodeLine &line, long lineNumber);
};


#endif //MONTADOR_SECONDPASSER_H