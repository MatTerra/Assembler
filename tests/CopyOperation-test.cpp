//
// Created by mateusberardo on 03/03/2021.
//
#include "gtest/gtest.h"
#include "operations/copyoperation.h"
#include "baseoperation.h"
#include <string>
#include <vector>

TEST(CopyOperation, may_instantiate_copyOperation){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    operands.insert(operands.cend(), 2);
    BaseOperation *copy = new CopyOperation(operands);
    ASSERT_TRUE(copy != nullptr);
}

TEST(CopyOperation, name_should_be_copy){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    operands.insert(operands.cend(), 2);
    BaseOperation *copy = new CopyOperation(operands);
    ASSERT_EQ("copy", copy->getOperation());
}

TEST(CopyOperation, address_size_should_be_3){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    operands.insert(operands.cend(), 2);
    BaseOperation *copy = new CopyOperation(operands);
    ASSERT_EQ(3, copy->getAddressSize());
}

TEST(CopyOperation, opcode_should_be_9){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    operands.insert(operands.cend(), 1);
    BaseOperation *copy = new CopyOperation(operands);
    ASSERT_EQ(9, copy->getOpCode());
}

TEST(CopyOperation, should_list_operands){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    operands.insert(operands.cend(), 2);
    BaseOperation *copy = new CopyOperation(operands);
    ASSERT_EQ(operands, copy->getOperands());
}

TEST(CopyOperation, should_be_valid_with_2_operand){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    operands.insert(operands.cend(), 2);
    BaseOperation *copy = new CopyOperation(operands);
    ASSERT_TRUE(copy->isValid());
}

TEST(CopyOperation, shouldnt_be_valid_with_1_operand){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *copy = new CopyOperation(operands);
    ASSERT_FALSE(copy->isValid());
}

TEST(CopyOperation, should_generate_output){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 0);
    operands.insert(operands.cend(), 1);
    BaseOperation *copy = new CopyOperation(operands);
    ASSERT_EQ("09 00 01", copy->getOutput());
}
