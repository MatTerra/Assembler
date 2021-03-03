//
// Created by mateusberardo on 03/03/2021.
//
#include "gtest/gtest.h"
#include "operations/muloperation.h"
#include "baseoperation.h"
#include <string>
#include <vector>

TEST(MulOperation, may_instantiate_mulOperation){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *mul = new MulOperation(operands);
    ASSERT_TRUE(mul != nullptr);
}

TEST(MulOperation, name_should_be_mul){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *mul = new MulOperation(operands);
    ASSERT_EQ("mul", mul->getOperation());
}

TEST(MulOperation, address_size_should_be_2){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *mul = new MulOperation(operands);
    ASSERT_EQ(2, mul->getAddressSize());
}

TEST(MulOperation, opcode_should_be_3){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *mul = new MulOperation(operands);
    ASSERT_EQ(3, mul->getOpCode());
}

TEST(MulOperation, should_list_operands){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *mul = new MulOperation(operands);
    ASSERT_EQ(operands, mul->getOperands());
}

TEST(MulOperation, should_be_valid_with_1_operand){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *mul = new MulOperation(operands);
    ASSERT_TRUE(mul->isValid());
}

TEST(MulOperation, shouldnt_be_valid_with_2_operands){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    operands.insert(operands.cend(), 2);
    BaseOperation *mul = new MulOperation(operands);
    ASSERT_FALSE(mul->isValid());
}

TEST(MulOperation, should_generate_output){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 0);
    BaseOperation *mul = new MulOperation(operands);
    ASSERT_EQ("03 00", mul->getOutput());
}
