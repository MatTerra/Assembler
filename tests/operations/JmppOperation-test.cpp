//
// Created by mateusberardo on 03/03/2021.
//
#include "gtest/gtest.h"
#include "operations/jmppoperation.h"
#include "baseoperation.h"
#include <string>
#include <vector>

TEST(JmppOperation, may_instantiate_jmppOperation){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *jmpp = new JmppOperation(operands);
    ASSERT_TRUE(jmpp != nullptr);
}

TEST(JmppOperation, name_should_be_jmpp){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *jmpp = new JmppOperation(operands);
    ASSERT_EQ("jmpp", jmpp->getOperation());
}

TEST(JmppOperation, address_size_should_be_2){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *jmpp = new JmppOperation(operands);
    ASSERT_EQ(2, jmpp->getAddressSize());
}

TEST(JmppOperation, opcode_should_be_7){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *jmpp = new JmppOperation(operands);
    ASSERT_EQ(7, jmpp->getOpCode());
}

TEST(JmppOperation, should_list_operands){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *jmpp = new JmppOperation(operands);
    ASSERT_EQ(operands, jmpp->getOperands());
}

TEST(JmppOperation, should_be_valid_with_1_operand){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *jmpp = new JmppOperation(operands);
    ASSERT_TRUE(jmpp->isValid());
}

TEST(JmppOperation, shouldnt_be_valid_with_2_operands){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    operands.insert(operands.cend(), "2");
    BaseOperation *jmpp = new JmppOperation(operands);
    ASSERT_FALSE(jmpp->isValid());
}

TEST(JmppOperation, should_generate_output){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "0");
    BaseOperation *jmpp = new JmppOperation(operands);
    ASSERT_EQ("07 00", jmpp->getOutput());
}
