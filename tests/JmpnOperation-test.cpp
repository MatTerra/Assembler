//
// Created by mateusberardo on 03/03/2021.
//
#include "gtest/gtest.h"
#include "operations/jmpnoperation.h"
#include "baseoperation.h"
#include <string>
#include <vector>

TEST(JmpnOperation, may_instantiate_jmpnOperation){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *jmpn = new JmpnOperation(operands);
    ASSERT_TRUE(jmpn != nullptr);
}

TEST(JmpnOperation, name_should_be_jmpn){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *jmpn = new JmpnOperation(operands);
    ASSERT_EQ("jmpn", jmpn->getOperation());
}

TEST(JmpnOperation, address_size_should_be_2){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *jmpn = new JmpnOperation(operands);
    ASSERT_EQ(2, jmpn->getAddressSize());
}

TEST(JmpnOperation, opcode_should_be_6){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *jmpn = new JmpnOperation(operands);
    ASSERT_EQ(6, jmpn->getOpCode());
}

TEST(JmpnOperation, should_list_operands){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *jmpn = new JmpnOperation(operands);
    ASSERT_EQ(operands, jmpn->getOperands());
}

TEST(JmpnOperation, should_be_valid_with_1_operand){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *jmpn = new JmpnOperation(operands);
    ASSERT_TRUE(jmpn->isValid());
}

TEST(JmpnOperation, shouldnt_be_valid_with_2_operands){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    operands.insert(operands.cend(), 2);
    BaseOperation *jmpn = new JmpnOperation(operands);
    ASSERT_FALSE(jmpn->isValid());
}

TEST(JmpnOperation, should_generate_output){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 0);
    BaseOperation *jmpn = new JmpnOperation(operands);
    ASSERT_EQ("06 00", jmpn->getOutput());
}
