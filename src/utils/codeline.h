//
// Created by mateusberardo on 26/02/2021.
//
#ifndef MONTADOR_CODELINE_H
#define MONTADOR_CODELINE_H

static const char *const whitespaces = " \t\r\f\v";

#include <string>
#include <utility>
#include "stringutils.cpp"


class CodeLine {
public:
    explicit CodeLine(std::string line);
    bool hasLabel();
    bool hasComment();
    bool hasOperation();
    bool hasOperands(){ return !operands.empty(); };
    std::string getRawLine(){ return rawLine; };
    std::string getLabel(){ return label; };
    std::string getComment(){ return comment; };
    std::string getOperation(){ return operation; };
    std::vector<std::string> getOperands(){ return operands; };

private:
    std::string rawLine;
    std::string label;
    std::string rawOperation;
    std::string operation;
    std::vector<std::string> operands;
    std::string comment;

    void extractLabel();
    void extractComment();
    void extractOperation();
    void extractRawOperation();
    void extractOperands();
};

#endif //MONTADOR_CODELINE_H
