//
// Created by mateusberardo on 26/02/2021.
//
#ifndef MONTADOR_MODULELINE_H
#define MONTADOR_MODULELINE_H

#include <string>
#include <utility>
#include "stringutils.h"
#include "baseoperation.h"
#include "processedline.h"

class ModuleLine : public ProcessedLine {
public:
    explicit ModuleLine(std::string line);
    bool operator==(ModuleLine other) const;
    BaseOperation *getOperation(){ return operation; };
    uint16_t getAddressSize() override;
    std::string getOpCode();

private:
    BaseOperation *operation;
    void extractOperation() override;
};

#endif //MONTADOR_MODULELINE_H
