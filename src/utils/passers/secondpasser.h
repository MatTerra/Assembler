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
        : codeLines(std::move(codeLines)), symbolTable(symbolTable),
          nowLine(startingLine){};

    void pass();

    std::string getProcessedLine(int line);
    std::vector<ParsingError> getErrors();

    int16_t getErrorCount();

    uint16_t getLineCount();

    std::vector<std::string> getProcessedLines();

    std::string getRelocationBitmap();

private:
    uint16_t nowLine;
    std::vector<CodeLine> codeLines;
    SymbolTable *symbolTable;
    std::vector<std::string> processedLines;
    std::vector<ParsingError> errors;
    std::string relocationBitmap;

    void
    addOpCodeToProcessedLine(CodeLine &line, std::ostringstream &processedLine);
    void addOperandsAddressesToProcessedLine(CodeLine &line,
                                             std::ostringstream &processedLine);
    void addFormattedOperandToProcessedLineIfValid(std::string &operand,
                                                   std::ostringstream &processedLine);
    void processOperation(CodeLine &line,
                          std::ostringstream &processedLine);
    void processLine(CodeLine &line);
    void validateOperation(CodeLine &line);
};


#endif //MONTADOR_SECONDPASSER_H
