//
// Created by mateusberardo on 28/02/2021.
//
#include "gtest/gtest.h"
#include "operations/publicoperation.h"
#include "baseoperation.h"
#include <string>
#include <vector>

TEST(PublicOperation, may_instantiate_publicoperation){
    std::vector<std::string> operands;
    BaseOperation *ext = new PublicOperation(operands);
    ASSERT_TRUE(ext != nullptr);
}

TEST(PublicOperation, name_should_be_public){
    std::vector<std::string> operands;
    BaseOperation *ext = new PublicOperation(operands);
    ASSERT_EQ("public", ext->getOperation());
}

TEST(PublicOperation, address_size_should_be_0){
    std::vector<std::string> operands;
    BaseOperation *ext = new PublicOperation(operands);
    ASSERT_EQ(0, ext->getAddressSize());
}

TEST(PublicOperation, opcode_should_be_0){
    std::vector<std::string> operands;
    BaseOperation *ext = new PublicOperation(operands);
    ASSERT_EQ(0, ext->getOpCode());
}

TEST(PublicOperation, should_list_operands){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *ext = new PublicOperation(operands);
    ASSERT_EQ(operands, ext->getOperands());
}

TEST(PublicOperation, shouldnt_be_valid_with_no_operand){
    std::vector<std::string> operands;
    BaseOperation *ext = new PublicOperation(operands);
    ASSERT_FALSE(ext->isValid());
}

TEST(PublicOperation, should_be_valid_with_1_operand){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    BaseOperation *ext = new PublicOperation(operands);
    ASSERT_TRUE(ext->isValid());
}

TEST(PublicOperation, shouldnt_be_valid_with_2_operands){
    std::vector<std::string> operands;
    operands.insert(operands.cend(), "1");
    operands.insert(operands.cend(), "2");
    BaseOperation *ext = new PublicOperation(operands);
    ASSERT_FALSE(ext->isValid());
}

TEST(PublicOperation, should_generate_output){
    std::vector<std::string> operands;
    BaseOperation *ext = new PublicOperation(operands);
    ASSERT_EQ("", ext->getOutput());
}
