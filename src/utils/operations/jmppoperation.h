//
// Created by mateusberardo on 03/03/2021.
//

#ifndef MONTADOR_JMPPOPERATION_H
#define MONTADOR_JMPPOPERATION_H

#include "baseoperation.h"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

class JmppOperation : public BaseOperation{
public:
    JmppOperation(std::vector<std::string> operands)
        :BaseOperation("jmpp", 2, 7, std::move(operands)){};
    std::string getOutput() override;
};


#endif //MONTADOR_JMPPOPERATION_H
