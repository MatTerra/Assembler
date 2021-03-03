//
// Created by mateusberardo on 03/03/2021.
//
#include "gtest/gtest.h"
#include "operations/storeoperation.h"
#include "baseoperation.h"
#include <string>
#include <vector>

TEST(StoreOperation, may_instantiate_storeOperation){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *store = new StoreOperation(operands);
    ASSERT_TRUE(store != nullptr);
}

TEST(StoreOperation, name_should_be_store){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *store = new StoreOperation(operands);
    ASSERT_EQ("store", store->getOperation());
}

TEST(StoreOperation, address_size_should_be_2){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *store = new StoreOperation(operands);
    ASSERT_EQ(2, store->getAddressSize());
}

TEST(StoreOperation, opcode_should_be_11){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *store = new StoreOperation(operands);
    ASSERT_EQ(11, store->getOpCode());
}

TEST(StoreOperation, should_list_operands){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *store = new StoreOperation(operands);
    ASSERT_EQ(operands, store->getOperands());
}

TEST(StoreOperation, should_be_valid_with_1_operand){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    BaseOperation *store = new StoreOperation(operands);
    ASSERT_TRUE(store->isValid());
}

TEST(StoreOperation, shouldnt_be_valid_with_2_operands){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 1);
    operands.insert(operands.cend(), 2);
    BaseOperation *store = new StoreOperation(operands);
    ASSERT_FALSE(store->isValid());
}

TEST(StoreOperation, should_generate_output){
    std::vector<uint16_t> operands;
    operands.insert(operands.cend(), 0);
    BaseOperation *store = new StoreOperation(operands);
    ASSERT_EQ("11 00", store->getOutput());
}
