//
// Created by mateusberardo on 01/03/2021.
//
#include "gtest/gtest.h"
#include "baseoperationfactory.h"
#include "baseoperation.h"


TEST(BaseOperationFactory, get_operation_factory_shoud_retorn_factory){
    auto operationFactory = getBaseOperationFactory();
    ASSERT_TRUE(operationFactory != nullptr);
}

TEST(BaseOperationFactory, create_unknow_should_return_nullptr){
    std::vector<uint16_t> operands;
    auto operationFactory = getBaseOperationFactory();
    auto unknownOperation = operationFactory->create("ad", operands);
    ASSERT_TRUE(unknownOperation == nullptr);
}

TEST(BaseOperationFactory_Add, create_add_should_return_add_operation){
    std::vector<uint16_t> operands;
    auto operationFactory = getBaseOperationFactory();
    auto addOperation = operationFactory->create("add", operands);
    ASSERT_TRUE(addOperation != nullptr);
    ASSERT_EQ("add", addOperation->getOperation());
    ASSERT_EQ(1, addOperation->getOpCode());
}

TEST(BaseOperationFactory_Add, create_should_find_if_capital){
    std::vector<uint16_t> operands;
    auto operationFactory = getBaseOperationFactory();
    auto addOperation = operationFactory->create("ADD", operands);
    ASSERT_TRUE(addOperation != nullptr);
    ASSERT_EQ("add", addOperation->getOperation());
    ASSERT_EQ(1, addOperation->getOpCode());
}

TEST(BaseOperationFactory_Sub, create_sub_should_return_sub_operation){
    std::vector<uint16_t> operands;
    auto operationFactory = getBaseOperationFactory();
    auto subOperation = operationFactory->create("sub", operands);
    ASSERT_TRUE(subOperation != nullptr);
    ASSERT_EQ("sub", subOperation->getOperation());
    ASSERT_EQ(2, subOperation->getOpCode());
}

TEST(BaseOperationFactory_Mul, create_mul_should_return_mul_operation){
    std::vector<uint16_t> operands;
    auto operationFactory = getBaseOperationFactory();
    auto mulOperation = operationFactory->create("MuL", operands);
    ASSERT_TRUE(mulOperation != nullptr);
    ASSERT_EQ("mul", mulOperation->getOperation());
    ASSERT_EQ(3, mulOperation->getOpCode());
}

TEST(BaseOperationFactory_Div, create_div_should_return_div_operation){
    std::vector<uint16_t> operands;
    auto operationFactory = getBaseOperationFactory();
    auto divOperation = operationFactory->create("Div", operands);
    ASSERT_TRUE(divOperation != nullptr);
    ASSERT_EQ("div", divOperation->getOperation());
    ASSERT_EQ(4, divOperation->getOpCode());
}

TEST(BaseOperationFactory_Jmp, create_jmp_should_return_jmp_operation){
    std::vector<uint16_t> operands;
    auto operationFactory = getBaseOperationFactory();
    auto jmpOperation = operationFactory->create("jmp", operands);
    ASSERT_TRUE(jmpOperation != nullptr);
    ASSERT_EQ("jmp", jmpOperation->getOperation());
    ASSERT_EQ(5, jmpOperation->getOpCode());
}

TEST(BaseOperationFactory_Jmpn, create_jmpn_should_return_jmpn_operation){
    std::vector<uint16_t> operands;
    auto operationFactory = getBaseOperationFactory();
    auto jmpnOperation = operationFactory->create("jmpn", operands);
    ASSERT_TRUE(jmpnOperation != nullptr);
    ASSERT_EQ("jmpn", jmpnOperation->getOperation());
    ASSERT_EQ(6, jmpnOperation->getOpCode());
}

TEST(BaseOperationFactory_Jmpp, create_jmpp_should_return_jmpp_operation){
    std::vector<uint16_t> operands;
    auto operationFactory = getBaseOperationFactory();
    auto jmppOperation = operationFactory->create("jmpp", operands);
    ASSERT_TRUE(jmppOperation != nullptr);
    ASSERT_EQ("jmpp", jmppOperation->getOperation());
    ASSERT_EQ(7, jmppOperation->getOpCode());
}