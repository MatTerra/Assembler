//
// Created by mateusberardo on 26/02/2021.
//
#ifndef MONTADOR_CODELINE_H
#define MONTADOR_CODELINE_H

#include <string>
#include <utility>
#include "stringutils.h"
#include "baseoperation.h"
#include "processedline.h"

class CodeLine : public ProcessedLine {
public:
    explicit CodeLine(std::string line);
    bool operator==(CodeLine other) const;
    BaseOperation *getOperation(){ return operation; };
    uint16_t getAddressSize() override;
    std::string getOpCode();

private:
    BaseOperation *operation;
    void extractOperation() override;
};

#endif //MONTADOR_CODELINE_H
