//
// Created by mateusberardo on 28/02/2021.
//
#include "gtest/gtest.h"
#include "operations/externoperation.h"
#include "baseoperation.h"
#include <string>
#include <vector>

TEST(ExternOperation, may_instantiate_externoperation){
    std::vector<std::string> operands;
    BaseOperation *ext = new ExternOperation(operands);
    ASSERT_TRUE(ext != nullptr);
}

TEST(ExternOperation, name_should_be_extern){
    std::vector<std::string> operands;
    BaseOperation *ext = new ExternOperation(operands);
    ASSERT_EQ("extern", ext->getOperation());
}

TEST(ExternOperation, address_size_should_be_0){
    std::vector<std::string> operands;
    BaseOperation *ext = new ExternOperation(operands);
    ASSERT_EQ(0, ext->getAddressSize());
}

TEST(ExternOperation, opcode_should_be_0){
    std::vector<std::string> operands;
    BaseOperation *ext = new ExternOperation(operands);
    ASSERT_EQ(0, ext->getOpCode());
}

TEST(ExternOperation, should_list_operands){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *ext = new ExternOperation(operands);
    ASSERT_EQ(operands, ext->getOperands());
}

//TEST(ExternOperation, should_set_operands){
//    std::vector<std::string> operands;
//    operands.insert(operands.cend(), "1");
//    BaseOperation *ext = new ExternOperation(operands);
//    operands.insert(operands.cend(), "2");
//    ext->setOperands(operands);
//    ASSERT_EQ(operands, ext->getOperands());
//}

TEST(ExternOperation, should_be_valid_with_no_operand){
    std::vector<std::string> operands;
    BaseOperation *ext = new ExternOperation(operands);
    ASSERT_TRUE(ext->isValid());
}

TEST(ExternOperation, shouldnt_be_valid_with_1_operand){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *ext = new ExternOperation(operands);
    ASSERT_FALSE(ext->isValid());
}

TEST(ExternOperation, shouldnt_be_valid_with_2_operands){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    operands.insert(operands.cend(), "2");
    BaseOperation *ext = new ExternOperation(operands);
    ASSERT_FALSE(ext->isValid());
}

TEST(ExternOperation, should_generate_output){
    std::vector<std::string> operands;
    BaseOperation *ext = new ExternOperation(operands);
    ASSERT_EQ("", ext->getOutput());
}
