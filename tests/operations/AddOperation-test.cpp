//
// Created by mateusberardo on 28/02/2021.
//
#include "gtest/gtest.h"
#include "operations/addoperation.h"
#include "baseoperation.h"
#include <string>
#include <vector>

TEST(AddOperation, may_instantiate_addoperation){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *add = new AddOperation(operands);
    ASSERT_TRUE(add != nullptr);
}

TEST(AddOperation, name_should_be_add){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *add = new AddOperation(operands);
    ASSERT_EQ("add", add->getOperation());
}

TEST(AddOperation, address_size_should_be_2){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *add = new AddOperation(operands);
    ASSERT_EQ(2, add->getAddressSize());
}

TEST(AddOperation, opcode_should_be_1){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *add = new AddOperation(operands);
    ASSERT_EQ(1, add->getOpCode());
}

TEST(AddOperation, should_list_operands){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *add = new AddOperation(operands);
    ASSERT_EQ(operands, add->getOperands());
}

//TEST(AddOperation, should_set_operands){
//    std::vector<std::string> operands;
//    operands.insert(operands.cend(), "1");
//    BaseOperation *add = new AddOperation(operands);
//    operands.insert(operands.cend(), "2");
//    add->setOperands(operands);
//    ASSERT_EQ(operands, add->getOperands());
//}

TEST(AddOperation, should_be_valid_with_1_operand){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *add = new AddOperation(operands);
    ASSERT_TRUE(add->isValid());
}

TEST(AddOperation, shouldnt_be_valid_with_2_operands){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    operands.insert(operands.cend(), "2");
    BaseOperation *add = new AddOperation(operands);
    ASSERT_FALSE(add->isValid());
}

TEST(AddOperation, should_generate_output){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *add = new AddOperation(operands);
    ASSERT_EQ("01 01", add->getOutput());
}
