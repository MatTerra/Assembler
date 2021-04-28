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
    std::vector<std::string> operands;
    auto operationFactory = getBaseOperationFactory();
    auto unknownOperation = operationFactory->create("ad", operands);
    ASSERT_TRUE(unknownOperation == nullptr);
}

TEST(BaseOperationFactory_Add, create_add_should_return_add_operation){
    std::vector<std::string> operands;
    auto operationFactory = getBaseOperationFactory();
    auto addOperation = operationFactory->create("add", operands);
    ASSERT_TRUE(addOperation != nullptr);
    ASSERT_EQ("add", addOperation->getOperation());
    ASSERT_EQ(1, addOperation->getOpCode());
}

TEST(BaseOperationFactory_Add, create_should_find_if_capital){
    std::vector<std::string> operands;
    auto operationFactory = getBaseOperationFactory();
    auto addOperation = operationFactory->create("ADD", operands);
    ASSERT_TRUE(addOperation != nullptr);
    ASSERT_EQ("add", addOperation->getOperation());
    ASSERT_EQ(1, addOperation->getOpCode());
}

TEST(BaseOperationFactory_Sub, create_sub_should_return_sub_operation){
    std::vector<std::string> operands;
    auto operationFactory = getBaseOperationFactory();
    auto subOperation = operationFactory->create("sub", operands);
    ASSERT_TRUE(subOperation != nullptr);
    ASSERT_EQ("sub", subOperation->getOperation());
    ASSERT_EQ(2, subOperation->getOpCode());
}

TEST(BaseOperationFactory_Mul, create_mul_should_return_mul_operation){
    std::vector<std::string> operands;
    auto operationFactory = getBaseOperationFactory();
    auto mulOperation = operationFactory->create("MuL", operands);
    ASSERT_TRUE(mulOperation != nullptr);
    ASSERT_EQ("mul", mulOperation->getOperation());
    ASSERT_EQ(3, mulOperation->getOpCode());
}

TEST(BaseOperationFactory_Div, create_div_should_return_div_operation){
    std::vector<std::string> operands;
    auto operationFactory = getBaseOperationFactory();
    auto divOperation = operationFactory->create("Div", operands);
    ASSERT_TRUE(divOperation != nullptr);
    ASSERT_EQ("div", divOperation->getOperation());
    ASSERT_EQ(4, divOperation->getOpCode());
}

TEST(BaseOperationFactory_Jmp, create_jmp_should_return_jmp_operation){
    std::vector<std::string> operands;
    auto operationFactory = getBaseOperationFactory();
    auto jmpOperation = operationFactory->create("jmp", operands);
    ASSERT_TRUE(jmpOperation != nullptr);
    ASSERT_EQ("jmp", jmpOperation->getOperation());
    ASSERT_EQ(5, jmpOperation->getOpCode());
}

TEST(BaseOperationFactory_Jmpn, create_jmpn_should_return_jmpn_operation){
    std::vector<std::string> operands;
    auto operationFactory = getBaseOperationFactory();
    auto jmpnOperation = operationFactory->create("jmpn", operands);
    ASSERT_TRUE(jmpnOperation != nullptr);
    ASSERT_EQ("jmpn", jmpnOperation->getOperation());
    ASSERT_EQ(6, jmpnOperation->getOpCode());
}

TEST(BaseOperationFactory_Jmpp, create_jmpp_should_return_jmpp_operation){
    std::vector<std::string> operands;
    auto operationFactory = getBaseOperationFactory();
    auto jmppOperation = operationFactory->create("jmpp", operands);
    ASSERT_TRUE(jmppOperation != nullptr);
    ASSERT_EQ("jmpp", jmppOperation->getOperation());
    ASSERT_EQ(7, jmppOperation->getOpCode());
}

TEST(BaseOperationFactory_Jmpz, create_jmpz_should_return_jmpz_operation){
    std::vector<std::string> operands;
    auto operationFactory = getBaseOperationFactory();
    auto jmpzOperation = operationFactory->create("jmpz", operands);
    ASSERT_TRUE(jmpzOperation != nullptr);
    ASSERT_EQ("jmpz", jmpzOperation->getOperation());
    ASSERT_EQ(8, jmpzOperation->getOpCode());
}

TEST(BaseOperationFactory_Copy, create_copy_should_return_copy_operation){
    std::vector<std::string> operands;
    auto operationFactory = getBaseOperationFactory();
    auto copyOperation = operationFactory->create("copy", operands);
    ASSERT_TRUE(copyOperation != nullptr);
    ASSERT_EQ("copy", copyOperation->getOperation());
    ASSERT_EQ(9, copyOperation->getOpCode());
}

TEST(BaseOperationFactory_Load, create_load_should_return_load_operation){
    std::vector<std::string> operands;
    auto operationFactory = getBaseOperationFactory();
    auto loadOperation = operationFactory->create("load", operands);
    ASSERT_TRUE(loadOperation != nullptr);
    ASSERT_EQ("load", loadOperation->getOperation());
    ASSERT_EQ(10, loadOperation->getOpCode());
}

TEST(BaseOperationFactory_Store, create_store_should_return_store_operation){
    std::vector<std::string> operands;
    auto operationFactory = getBaseOperationFactory();
    auto storeOperation = operationFactory->create("store", operands);
    ASSERT_TRUE(storeOperation != nullptr);
    ASSERT_EQ("store", storeOperation->getOperation());
    ASSERT_EQ(11, storeOperation->getOpCode());
}

TEST(BaseOperationFactory_Input, create_input_should_return_input_operation){
    std::vector<std::string> operands;
    auto operationFactory = getBaseOperationFactory();
    auto inputOperation = operationFactory->create("input", operands);
    ASSERT_TRUE(inputOperation != nullptr);
    ASSERT_EQ("input", inputOperation->getOperation());
    ASSERT_EQ(12, inputOperation->getOpCode());
}

TEST(BaseOperationFactory_Output, create_output_should_return_output_operation){
    std::vector<std::string> operands;
    auto operationFactory = getBaseOperationFactory();
    auto outputOperation = operationFactory->create("output", operands);
    ASSERT_TRUE(outputOperation != nullptr);
    ASSERT_EQ("output", outputOperation->getOperation());
    ASSERT_EQ(13, outputOperation->getOpCode());
}

TEST(BaseOperationFactory_Output, create_extern_should_return_extern_operation){
    std::vector<std::string> operands;
    auto operationFactory = getBaseOperationFactory();
    auto externOperation = operationFactory->create("extern", operands);
    ASSERT_TRUE(externOperation != nullptr);
    ASSERT_EQ("extern", externOperation->getOperation());
    ASSERT_EQ(0, externOperation->getOpCode());
}