//
// Created by mateusberardo on 28/02/2021.
//
#include "gtest/gtest.h"
#include "symboltable.h"
#include "symbolnotfoundexception.h"
#include <string>

TEST(SymbolTable, may_get_symboltable_instance){
    auto *st = SymbolTable::getInstance();
    ASSERT_TRUE(st != nullptr);
}

TEST(SymbolTable, get_instance_returns_always_the_same){
    auto *st = SymbolTable::getInstance();
    auto *st2 = SymbolTable::getInstance();
    ASSERT_EQ(st, st2);
}

TEST(SymbolTable_Symbol, symbol_count_should_be_0_on_start){
    auto *st = SymbolTable::getInstance();
    ASSERT_EQ(0, st->getSymbolCount());
    delete st;
}

TEST(SymbolTable_Symbol, should_be_able_to_add_symbol){
    auto *st = SymbolTable::getInstance();
    st->addSymbol("test", 0);
    ASSERT_EQ(1, st->getSymbolCount());
    delete st;
}

TEST(SymbolTable_Symbol, symbol_should_not_exist_before_adding){
    auto *st = SymbolTable::getInstance();
    ASSERT_FALSE(st->hasSymbol("test"));
    delete st;
}

TEST(SymbolTable_Symbol, symbol_should_exist_after_adding){
    auto *st = SymbolTable::getInstance();
    st->addSymbol("test", 0);
    ASSERT_TRUE(st->hasSymbol("test"));
    delete st;
}

TEST(SymbolTable_Address, should_return_symbol_address){
    auto *st = SymbolTable::getInstance();
    st->addSymbol("test", 2);
    ASSERT_EQ(2, st->getSymbolAddress("test"));
    delete st;
}

TEST(SymbolTable_Address, should_thrown_not_found_if_not_found){
    auto *st = SymbolTable::getInstance();
    ASSERT_THROW(st->getSymbolAddress("test"), SymbolNotFoundException);
    delete st;
}

TEST(SymbolTable_Address, exception_should_have_symbol_in_what){
    auto *st = SymbolTable::getInstance();
    try {
        st->getSymbolAddress("test");
    } catch (SymbolNotFoundException& exception) {
        ASSERT_TRUE(exception.what() == std::string("test"));
    }
    delete st;
}