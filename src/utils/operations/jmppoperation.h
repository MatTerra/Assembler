//
// Created by mateusberardo on 03/03/2021.
//

#ifndef MONTADOR_JMPPOPERATION_H
#define MONTADOR_JMPPOPERATION_H

#include "baseoperation.h"
#include <vector>
#include <sstream>
#include <iomanip>

class JmppOperation : public BaseOperation{
public:
    JmppOperation(std::vector<uint16_t> operands)
        :BaseOperation("jmpp", 2, 7, std::move(operands)){};
    std::string getOutput() override;
};


#endif //MONTADOR_JMPPOPERATION_H
