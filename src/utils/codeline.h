//
// Created by mateusberardo on 26/02/2021.
//
#ifndef MONTADOR_CODELINE_H
#define MONTADOR_CODELINE_H

#include <string>
#include <utility>
#include "stringutils.h"
#include "baseoperation.h"


class CodeLine {
public:
    explicit CodeLine(std::string line);
    bool hasLabel();
    bool hasComment();
    bool hasOperation();
    bool hasOperands(){ return !operands.empty(); };
    bool operator==(CodeLine other) const;
    std::string getRawLine() const { return rawLine; } ;
    std::string getLabel(){ return label; };
    std::string getComment(){ return comment; };
    std::string getOperationMnemonic(){ return operationMnemonic; };
    BaseOperation *getOperation(){ return operation; };
    std::vector<std::string> getOperands(){ return operands; };

    uint16_t getAddressSize();

    std::string getOpCode();

private:
    std::string rawLine;
    std::string label;
    std::string rawOperation;
    std::string operationMnemonic;
    BaseOperation *operation;
    std::vector<std::string> operands;
    std::string comment;

    void extractLabel();
    void extractComment();
    void extractOperationMnemonic();
    void extractRawOperation();
    void extractOperands();
    void extractOperation();
};

#endif //MONTADOR_CODELINE_H
