//
// Created by mateusberardo on 28/02/2021.
//

#ifndef MONTADOR_BASEOPERATION_H
#define MONTADOR_BASEOPERATION_H

#include <string>
#include <utility>
#include <vector>

class BaseOperation{
public:
    uint16_t getAddressSize() const{ return addressSize; };
    uint16_t getOpCode() const{ return opCode; };
    std::string getOperation() const{ return operation; };
    std::vector<uint16_t> getOperands() const{ return operands; };
    bool isValid() { return operands.size() == addressSize-1; };
    virtual std::string getOutput() = 0;
protected:
    BaseOperation(std::string operation, uint16_t addressSize,
                  uint16_t opCode, std::vector<uint16_t> operands)
        :operation(std::move(operation)), addressSize(addressSize),
        opCode(opCode), operands(std::move(operands)){};
    std::string operation;
    uint16_t addressSize;
    uint16_t opCode;
    std::vector<uint16_t> operands;
};

#endif //MONTADOR_BASEOPERATION_H
