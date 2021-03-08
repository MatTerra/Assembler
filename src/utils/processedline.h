//
// Created by mateusberardo on 08/03/2021.
//

#ifndef MONTADOR_PROCESSEDLINE_H
#define MONTADOR_PROCESSEDLINE_H

#include <utility>
#include <vector>
#include <string>

class ProcessedLine {
public:
    explicit ProcessedLine(std::string line);

    std::string getRawLine() const { return rawLine; };
    std::string getLabel() { return label; };
    bool hasLabel();
    std::string getComment() { return comment; };
    bool hasComment();
    bool hasOperation();
    std::string getOperationMnemonic(){ return operationMnemonic; };
    std::vector<std::string> getOperands() { return operands; }
    bool hasOperands() { return !operands.empty(); }
    virtual uint16_t getAddressSize() = 0;

protected:
    std::string rawLine;
    std::string label;
    std::string comment;
    std::string rawOperation;
    std::string operationMnemonic;
    std::vector<std::string> operands;

    void extractLabel();
    void extractComment();
    void extractRawOperation();
    void extractOperationMnemonic();
    void extractOperands();
    virtual void extractOperation() = 0;
};


#endif //MONTADOR_PROCESSEDLINE_H
