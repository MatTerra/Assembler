//
// Created by mateusberardo on 28/02/2021.
//
#include "gtest/gtest.h"
#include "symboltable.h"
#include "exceptions/symbolnotfoundexception.h"
#include <string>
#include <exceptions/symbolalreadyexistsexception.h>

TEST(SymbolTable, may_get_symboltable_instance){
    auto *st = new SymbolTable();
    ASSERT_TRUE(st != nullptr);
}

TEST(SymbolTable, get_instance_returns_always_the_same){
    auto *st = new SymbolTable();
    auto *st2 = new SymbolTable();
    ASSERT_NE(st, st2);
}

TEST(SymbolTable_Symbol, symbol_count_should_be_0_on_start){
    auto *st = new SymbolTable();
    ASSERT_EQ(0, st->getSymbolCount());
}

TEST(SymbolTable_Symbol, should_be_able_to_add_symbol){
    auto *st = new SymbolTable();
    st->addSymbol("test", 0);
    ASSERT_EQ(1, st->getSymbolCount());
}

TEST(SymbolTable_Symbol, symbol_should_not_exist_before_adding){
    auto *st = new SymbolTable();
    ASSERT_FALSE(st->hasSymbol("test"));
}

TEST(SymbolTable_Symbol, symbol_should_exist_after_adding){
    auto *st = new SymbolTable();
    st->addSymbol("test", 0);
    ASSERT_TRUE(st->hasSymbol("test"));
}

TEST(SymbolTable_Symbol, symbol_should_be_case_insensitive){
    auto *st = new SymbolTable();
    st->addSymbol("test", 0);
    ASSERT_TRUE(st->hasSymbol("tESt"));
}

TEST(SymbolTable_Symbol, should_validate_symbol){
    ASSERT_FALSE(SymbolTable::isValidSymbol("test test"));
    ASSERT_FALSE(SymbolTable::isValidSymbol("test "));
    ASSERT_FALSE(SymbolTable::isValidSymbol("8test"));
    ASSERT_FALSE(SymbolTable::isValidSymbol("test,test"));
    ASSERT_FALSE(SymbolTable::isValidSymbol("testtesttesttesttestt"));
    ASSERT_FALSE(SymbolTable::isValidSymbol(""));
}

TEST(SymbolTable_Symbol, should_validate_symbol_when_ok){
    ASSERT_TRUE(SymbolTable::isValidSymbol("test_"));
}

TEST(SymbolTable_Symbol, add_duplicate_symbol_should_throw_exception){
    auto *st = new SymbolTable();
    st->addSymbol("test", 0);
    ASSERT_THROW(st->addSymbol("test", 1), SymbolAlreadyExistsException);
}

TEST(SymbolTable_Address, should_return_symbol_address){
    auto *st = new SymbolTable();
    st->addSymbol("test", 2);
    ASSERT_EQ(2, st->getSymbolAddress("test"));
}

TEST(SymbolTable_Address, should_thrown_not_found_if_not_found){
    auto *st = new SymbolTable();
    ASSERT_THROW(st->getSymbolAddress("test"), SymbolNotFoundException);
}

TEST(SymbolTable_Address, exception_should_have_symbol_in_what){
    auto *st = new SymbolTable();
    try {
        st->getSymbolAddress("test");
    } catch (SymbolNotFoundException& exception) {
        ASSERT_TRUE(exception.what() == std::string("test"));
    }
}