//
// Created by mateusberardo on 24/02/2021.
//
#include "gtest/gtest.h"
#include "preprocessor.h"

TEST (PreProcessor, may_instantiate_preprocessor){
    PreProcessor* a = new PreProcessor();
    ASSERT_TRUE(a != nullptr);
}

