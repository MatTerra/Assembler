//
// Created by mateusberardo on 26/02/2021.
//
#include <iostream>
#include <vector>
#include "codeline.h"

CodeLine::CodeLine(std::string line) :rawLine(std::move(line)){
    if (hasLabel())
        extractLabel();
    if (hasComment())
        extractComment();
    extractRawOperation();
    if (hasOperation()){
        extractOperation();
        extractOperands();
    }
}

bool CodeLine::hasLabel() {
    return rawLine.find(':') != std::string::npos;
}

void CodeLine::extractLabel() {
    label = rawLine.substr(0, rawLine.find(':'));
    removeLeadingWhitespaces(label);
}

bool CodeLine::hasComment() {
    return rawLine.find(';') != std::string::npos;
}

void CodeLine::extractComment() {
    comment = rawLine.substr(rawLine.find(';') + 1);
}

void CodeLine::extractRawOperation(){
    size_t labelEnd = rawLine.find(":") + 1;
    size_t commentStart = rawLine.find(";");

    rawOperation = rawLine.substr(labelEnd, commentStart - labelEnd);
    trim(rawOperation);
}

bool CodeLine::hasOperation() {
    return rawOperation.length() > 0;
}

void CodeLine::extractOperation() {
    operation = rawOperation.substr(0,
                                    rawOperation.find_first_of(whitespaces));
}

void CodeLine::extractOperands() {
    if(rawOperation.find_first_of(whitespaces) == std::string::npos)
        return;
    auto rawOperands = rawOperation.substr(
            rawOperation.find_first_of(whitespaces));
    size_t initPos = 0;
    while (initPos != std::string::npos){
        auto nextPos = rawOperands.find(',', initPos+1);
        auto operand = rawOperands.substr(initPos+1, nextPos-1);
        trim(operand);
        initPos = nextPos;
        operands.insert(operands.cend(), operand);
    }
}

