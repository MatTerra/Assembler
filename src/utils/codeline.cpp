//
// Created by mateusberardo on 26/02/2021.
//
#include <iostream>
#include "codeline.h"

CodeLine::CodeLine(std::string line) :rawLine(std::move(line)){
    if (hasLabel())
        extractLabel();
    if (hasComment())
        extractComment();
    if (hasOperation()){
        extractOperation();
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

bool CodeLine::hasOperation() {
    std::string operation = getRawOperation();
    return operation.length() > 0;
}

std::string CodeLine::getRawOperation() const {
    int labelEnd = rawLine.find(":") + 1;
    int commentStart = rawLine.find(";");

    auto rawOperation = rawLine.substr(labelEnd, commentStart - labelEnd);
    removeLeadingWhitespaces(rawOperation);

    return rawOperation;
}

void CodeLine::extractOperation() {
    auto rawOperation = getRawOperation();
    operation = rawOperation.substr(0, rawOperation.find_first_of(whitespaces));
}


