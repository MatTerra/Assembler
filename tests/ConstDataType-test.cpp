//
// Created by mateusberardo on 08/03/2021.
//

#include <datatypes/constdatatype.h>
#include "gtest/gtest.h"

TEST(ConstDataType, may_instantiate){
    auto space = new ConstDataType("test", "0");
    ASSERT_NE(nullptr, space);
}

TEST(ConstDataType, should_get_symbol){
    auto space = new ConstDataType("test", "0");
    ASSERT_EQ("test", space->getSymbol());
}

TEST(ConstDataType, should_get_int_value){
    auto space = new ConstDataType("test", "0");
    ASSERT_EQ(0, space->getValue());
}

TEST(ConstDataType, should_get_int_negative_value){
    auto space = new ConstDataType("test", "-2");
    ASSERT_EQ(-2, space->getValue());
}