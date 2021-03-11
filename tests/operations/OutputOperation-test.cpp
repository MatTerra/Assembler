//
// Created by mateusberardo on 03/03/2021.
//
#include "gtest/gtest.h"
#include "operations/outputoperation.h"
#include "baseoperation.h"
#include <string>
#include <vector>

TEST(OutputOperation, may_instantiate_outputOperation){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *output = new OutputOperation(operands);
    ASSERT_TRUE(output != nullptr);
}

TEST(OutputOperation, name_should_be_output){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *output = new OutputOperation(operands);
    ASSERT_EQ("output", output->getOperation());
}

TEST(OutputOperation, address_size_should_be_2){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *output = new OutputOperation(operands);
    ASSERT_EQ(2, output->getAddressSize());
}

TEST(OutputOperation, opcode_should_be_13){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *output = new OutputOperation(operands);
    ASSERT_EQ(13, output->getOpCode());
}

TEST(OutputOperation, should_list_operands){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *output = new OutputOperation(operands);
    ASSERT_EQ(operands, output->getOperands());
}

TEST(OutputOperation, should_be_valid_with_1_operand){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *output = new OutputOperation(operands);
    ASSERT_TRUE(output->isValid());
}

TEST(OutputOperation, shouldnt_be_valid_with_2_operands){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    operands.insert(operands.cend(), "2");
    BaseOperation *output = new OutputOperation(operands);
    ASSERT_FALSE(output->isValid());
}

TEST(OutputOperation, should_generate_output){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "0");
    BaseOperation *output = new OutputOperation(operands);
    ASSERT_EQ("13 00", output->getOutput());
}
