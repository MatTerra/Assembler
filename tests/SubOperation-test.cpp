//
// Created by mateusberardo on 02/03/2021.
//
#include "gtest/gtest.h"
#include "operations/suboperation.h"
#include "baseoperation.h"
#include <string>
#include <vector>

TEST(SubOperation, may_instantiate_subOperation){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *sub = new SubOperation(operands);
    ASSERT_TRUE(sub != nullptr);
}

TEST(SubOperation, name_should_be_sub){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *sub = new SubOperation(operands);
    ASSERT_EQ("sub", sub->getOperation());
}

TEST(SubOperation, address_size_should_be_2){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *sub = new SubOperation(operands);
    ASSERT_EQ(2, sub->getAddressSize());
}

TEST(SubOperation, opcode_should_be_2){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *sub = new SubOperation(operands);
    ASSERT_EQ(2, sub->getOpCode());
}

TEST(SubOperation, should_list_operands){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *sub = new SubOperation(operands);
    ASSERT_EQ(operands, sub->getOperands());
}

TEST(SubOperation, should_be_valid_with_1_operand){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *sub = new SubOperation(operands);
    ASSERT_TRUE(sub->isValid());
}

TEST(SubOperation, shouldnt_be_valid_with_2_operands){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    operands.insert(operands.cend(), 2);
    BaseOperation *sub = new SubOperation(operands);
    ASSERT_FALSE(sub->isValid());
}

TEST(SubOperation, should_generate_output){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 0);
    BaseOperation *sub = new SubOperation(operands);
    ASSERT_EQ("02 00", sub->getOutput());
}
