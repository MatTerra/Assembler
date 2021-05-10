//
// Created by mateusberardo on 10/05/2021.
//
#include <passers/modulepasser.h>
#include <parsingerrors/missinglabelerror.h>
#include "gtest/gtest.h"

TEST(ModulePasser, extern_with_no_label_shoul_generate_error) {
    auto *firstPasser = new ModulePasser("extern\n",1);
    firstPasser->pass();
    ASSERT_EQ(MissingLabelError(1).what(),
              firstPasser->getErrors()[0].what());
}

TEST(ModulePasser, should_generate_extern_symbol) {
    auto *firstPasser = new ModulePasser("try: extern\n", 0);
    firstPasser->pass();
    ASSERT_TRUE(firstPasser->getSymbolTable()->isExternSymbol("try"));
}

TEST(ModulePasser, should_set_public_symbol) {
    SymbolTable st;
    st.addSymbol("test", 1);
    auto *firstPasser = new ModulePasser("public test\n", 0, &st);
    firstPasser->pass();
    ASSERT_TRUE(firstPasser->getSymbolTable()->isPublicSymbol("test"));
    ASSERT_EQ(1, firstPasser->getSymbolTable()->getSymbolAddress("test"));
}

