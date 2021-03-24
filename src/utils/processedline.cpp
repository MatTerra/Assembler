//
// Created by mateusberardo on 08/03/2021.
//

#include "processedline.h"

ProcessedLine::ProcessedLine(std::string line) :rawLine(std::move(line)) {
    if (hasLabel())
        extractLabel();
    if (hasComment())
        extractComment();
    extractRawOperation();
    if (hasOperation()){
        extractOperationMnemonic();
        extractOperands();
     }
}

bool ProcessedLine::hasLabel() {
    auto possibleLine = rawLine.substr(0, rawLine.find_first_of(';'));

    return possibleLine.find(':') != std::string::npos;
}

void ProcessedLine::extractLabel() {
    label = rawLine.substr(0, rawLine.find(':'));
    trim(label);
}

bool ProcessedLine::hasComment() {
    return rawLine.find(';') != std::string::npos;
}

void ProcessedLine::extractComment() {
    comment = rawLine.substr(rawLine.find_first_of(';') + 1);
}

void ProcessedLine::extractRawOperation(){
    size_t labelEnd = rawLine.find_last_of(':', rawLine.find_first_of(';')) + 1;
    size_t commentStart = rawLine.find(';');

    rawOperation = rawLine.substr(labelEnd, commentStart - labelEnd);
    trim(rawOperation);
}

bool ProcessedLine::hasOperation() {
    return rawOperation.length() > 0;
}

void ProcessedLine::extractOperationMnemonic() {
    operationMnemonic = rawOperation.substr(
            0,
            rawOperation.find_first_of(whitespaces));
}

void ProcessedLine::extractOperands() {
    if(rawOperation.find_first_of(whitespaces) == std::string::npos)
        return;
    auto rawOperands = rawOperation.substr(
            rawOperation.find_first_of(whitespaces));
    size_t initPos = 0;
    while (initPos != std::string::npos){
        auto nextPos = rawOperands.find(',', initPos+1);
        auto operand = rawOperands.substr(initPos+1, (nextPos-1)-initPos);
        trim(operand);
        initPos = nextPos;
        operands.insert(operands.cend(), operand);
    }
}
