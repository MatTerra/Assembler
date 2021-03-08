//
// Created by mateusberardo on 08/03/2021.
//

#include <datatypes/spacedatatype.h>
#include "gtest/gtest.h"

TEST(SpaceDataType, may_instantiate){
    auto space = new SpaceDataType("test");
    ASSERT_NE(nullptr, space);
}

TEST(SpaceDataType, should_get_symbol){
    auto space = new SpaceDataType("test");
    ASSERT_EQ("test", space->getSymbol());
}

TEST(SpaceDataType, should_get_int_value){
    auto space = new SpaceDataType("test");
    ASSERT_EQ(0, space->getValue());
}