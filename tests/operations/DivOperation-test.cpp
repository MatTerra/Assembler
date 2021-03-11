//
// Created by mateusberardo on 03/03/2021.
//
#include "gtest/gtest.h"
#include "operations/divoperation.h"
#include "baseoperation.h"
#include <string>
#include <vector>

TEST(DivOperation, may_instantiate_divOperation){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *div = new DivOperation(operands);
    ASSERT_TRUE(div != nullptr);
}

TEST(DivOperation, name_should_be_div){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *div = new DivOperation(operands);
    ASSERT_EQ("div", div->getOperation());
}

TEST(DivOperation, address_size_should_be_2){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *div = new DivOperation(operands);
    ASSERT_EQ(2, div->getAddressSize());
}

TEST(DivOperation, opcode_should_be_4){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *div = new DivOperation(operands);
    ASSERT_EQ(4, div->getOpCode());
}

TEST(DivOperation, should_list_operands){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *div = new DivOperation(operands);
    ASSERT_EQ(operands, div->getOperands());
}

TEST(DivOperation, should_be_valid_with_1_operand){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *div = new DivOperation(operands);
    ASSERT_TRUE(div->isValid());
}

TEST(DivOperation, shouldnt_be_valid_with_2_operands){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    operands.insert(operands.cend(), "2");
    BaseOperation *div = new DivOperation(operands);
    ASSERT_FALSE(div->isValid());
}

TEST(DivOperation, should_generate_output){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "0");
    BaseOperation *div = new DivOperation(operands);
    ASSERT_EQ("04 00", div->getOutput());
}
