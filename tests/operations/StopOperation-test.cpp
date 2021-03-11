//
// Created by mateusberardo on 03/03/2021.
//
#include "gtest/gtest.h"
#include "operations/stopoperation.h"
#include "baseoperation.h"
#include <string>
#include <vector>

TEST(StopOperation, may_instantiate_stopOperation){
    std::vector<std::string> operands;
    BaseOperation *stop = new StopOperation(operands);
    ASSERT_TRUE(stop != nullptr);
}

TEST(StopOperation, name_should_be_stop){
    std::vector<std::string> operands;
    BaseOperation *stop = new StopOperation(operands);
    ASSERT_EQ("stop", stop->getOperation());
}

TEST(StopOperation, address_size_should_be_1){
    std::vector<std::string> operands;
    BaseOperation *stop = new StopOperation(operands);
    ASSERT_EQ(1, stop->getAddressSize());
}

TEST(StopOperation, opcode_should_be_14){
    std::vector<std::string> operands;
    BaseOperation *stop = new StopOperation(operands);
    ASSERT_EQ(14, stop->getOpCode());
}

TEST(StopOperation, should_list_operands){
    std::vector<std::string> operands;
    BaseOperation *stop = new StopOperation(operands);
    ASSERT_EQ(operands, stop->getOperands());
}

TEST(StopOperation, should_be_valid_with_0_operand){
    std::vector<std::string> operands;
    BaseOperation *stop = new StopOperation(operands);
    ASSERT_TRUE(stop->isValid());
}

TEST(StopOperation, shouldnt_be_valid_with_1_operands){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *stop = new StopOperation(operands);
    ASSERT_FALSE(stop->isValid());
}

TEST(StopOperation, should_generate_output){
    std::vector<std::string> operands;
    BaseOperation *stop = new StopOperation(operands);
    ASSERT_EQ("14", stop->getOutput());
}
