//
// Created by mateusberardo on 03/03/2021.
//
#include "gtest/gtest.h"
#include "operations/jmpzoperation.h"
#include "baseoperation.h"
#include <string>
#include <vector>

TEST(JmpzOperation, may_instantiate_jmpzOperation){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *jmpz = new JmpzOperation(operands);
    ASSERT_TRUE(jmpz != nullptr);
}

TEST(JmpzOperation, name_should_be_jmpz){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *jmpz = new JmpzOperation(operands);
    ASSERT_EQ("jmpz", jmpz->getOperation());
}

TEST(JmpzOperation, address_size_should_be_2){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *jmpz = new JmpzOperation(operands);
    ASSERT_EQ(2, jmpz->getAddressSize());
}

TEST(JmpzOperation, opcode_should_be_8){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *jmpz = new JmpzOperation(operands);
    ASSERT_EQ(8, jmpz->getOpCode());
}

TEST(JmpzOperation, should_list_operands){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *jmpz = new JmpzOperation(operands);
    ASSERT_EQ(operands, jmpz->getOperands());
}

TEST(JmpzOperation, should_be_valid_with_1_operand){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *jmpz = new JmpzOperation(operands);
    ASSERT_TRUE(jmpz->isValid());
}

TEST(JmpzOperation, shouldnt_be_valid_with_2_operands){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    operands.insert(operands.cend(), 2);
    BaseOperation *jmpz = new JmpzOperation(operands);
    ASSERT_FALSE(jmpz->isValid());
}

TEST(JmpzOperation, should_generate_output){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 0);
    BaseOperation *jmpz = new JmpzOperation(operands);
    ASSERT_EQ("08 00", jmpz->getOutput());
}
