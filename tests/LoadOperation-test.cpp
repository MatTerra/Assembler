//
// Created by mateusberardo on 03/03/2021.
//
#include "gtest/gtest.h"
#include "operations/loadoperation.h"
#include "baseoperation.h"
#include <string>
#include <vector>

TEST(LoadOperation, may_instantiate_loadOperation){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *load = new LoadOperation(operands);
    ASSERT_TRUE(load != nullptr);
}

TEST(LoadOperation, name_should_be_load){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *load = new LoadOperation(operands);
    ASSERT_EQ("load", load->getOperation());
}

TEST(LoadOperation, address_size_should_be_2){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *load = new LoadOperation(operands);
    ASSERT_EQ(2, load->getAddressSize());
}

TEST(LoadOperation, opcode_should_be_10){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *load = new LoadOperation(operands);
    ASSERT_EQ(10, load->getOpCode());
}

TEST(LoadOperation, should_list_operands){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *load = new LoadOperation(operands);
    ASSERT_EQ(operands, load->getOperands());
}

TEST(LoadOperation, should_be_valid_with_1_operand){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *load = new LoadOperation(operands);
    ASSERT_TRUE(load->isValid());
}

TEST(LoadOperation, shouldnt_be_valid_with_2_operands){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    operands.insert(operands.cend(), 2);
    BaseOperation *load = new LoadOperation(operands);
    ASSERT_FALSE(load->isValid());
}

TEST(LoadOperation, should_generate_output){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 0);
    BaseOperation *load = new LoadOperation(operands);
    ASSERT_EQ("10 00", load->getOutput());
}
