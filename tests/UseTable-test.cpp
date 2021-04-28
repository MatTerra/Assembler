//
// Created by mateusberardo on 28/04/2021.
//
#include "gtest/gtest.h"
#include <usetable.h>

TEST(UseTable, should_be_able_instantiate){
    auto *ut = new UseTable();
    ASSERT_NE(nullptr, ut);
}

TEST(UseTable, may_add_use){
    auto *ut = new UseTable();
    ASSERT_NO_THROW(ut->addSymbolUse("test", 1));
}

TEST(UseTable, may_get_use_list){
    auto *ut = new UseTable();
    ut->addSymbolUse("test", 1);
    std::vector<uint16_t> uses;
    uses.insert(uses.end(), 1);
    ASSERT_EQ(uses, ut->getSymbolUse("test"));
}

TEST(UseTable, may_get_used_symbols){
    auto *ut = new UseTable();
    ut->addSymbolUse("test",1);
    ut->addSymbolUse("test",3);
    ut->addSymbolUse("ok",2);
    std::vector<std::string> usedSymbols;
    usedSymbols.insert(usedSymbols.end(),"ok");
    usedSymbols.insert(usedSymbols.end(),"test");
    ASSERT_EQ(usedSymbols, ut->getUsedSymbols());
}
