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