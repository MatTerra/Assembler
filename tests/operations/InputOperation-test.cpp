//
// Created by mateusberardo on 03/03/2021.
//
#include "gtest/gtest.h"
#include "operations/inputoperation.h"
#include "baseoperation.h"
#include <string>
#include <vector>

TEST(InputOperation, may_instantiate_inputOperation){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *input = new InputOperation(operands);
    ASSERT_TRUE(input != nullptr);
}

TEST(InputOperation, name_should_be_input){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *input = new InputOperation(operands);
    ASSERT_EQ("input", input->getOperation());
}

TEST(InputOperation, address_size_should_be_2){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *input = new InputOperation(operands);
    ASSERT_EQ(2, input->getAddressSize());
}

TEST(InputOperation, opcode_should_be_12){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *input = new InputOperation(operands);
    ASSERT_EQ(12, input->getOpCode());
}

TEST(InputOperation, should_list_operands){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *input = new InputOperation(operands);
    ASSERT_EQ(operands, input->getOperands());
}

TEST(InputOperation, should_be_valid_with_1_operand){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *input = new InputOperation(operands);
    ASSERT_TRUE(input->isValid());
}

TEST(InputOperation, shouldnt_be_valid_with_2_operands){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    operands.insert(operands.cend(), "2");
    BaseOperation *input = new InputOperation(operands);
    ASSERT_FALSE(input->isValid());
}

TEST(InputOperation, should_generate_output){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "0");
    BaseOperation *input = new InputOperation(operands);
    ASSERT_EQ("12 00", input->getOutput());
}
