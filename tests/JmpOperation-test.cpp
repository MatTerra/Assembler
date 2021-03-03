//
// Created by mateusberardo on 03/03/2021.
//
#include "gtest/gtest.h"
#include "operations/jmpoperation.h"
#include "baseoperation.h"
#include <string>
#include <vector>

TEST(JmpOperation, may_instantiate_jmpOperation){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *jmp = new JmpOperation(operands);
    ASSERT_TRUE(jmp != nullptr);
}

TEST(JmpOperation, name_should_be_jmp){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *jmp = new JmpOperation(operands);
    ASSERT_EQ("jmp", jmp->getOperation());
}

TEST(JmpOperation, address_size_should_be_2){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *jmp = new JmpOperation(operands);
    ASSERT_EQ(2, jmp->getAddressSize());
}

TEST(JmpOperation, opcode_should_be_5){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *jmp = new JmpOperation(operands);
    ASSERT_EQ(5, jmp->getOpCode());
}

TEST(JmpOperation, should_list_operands){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *jmp = new JmpOperation(operands);
    ASSERT_EQ(operands, jmp->getOperands());
}

TEST(JmpOperation, should_be_valid_with_1_operand){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *jmp = new JmpOperation(operands);
    ASSERT_TRUE(jmp->isValid());
}

TEST(JmpOperation, shouldnt_be_valid_with_2_operands){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    operands.insert(operands.cend(), 2);
    BaseOperation *jmp = new JmpOperation(operands);
    ASSERT_FALSE(jmp->isValid());
}

TEST(JmpOperation, should_generate_output){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 0);
    BaseOperation *jmp = new JmpOperation(operands);
    ASSERT_EQ("05 00", jmp->getOutput());
}
