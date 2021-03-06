//
// Created by mateusberardo on 28/02/2021.
//
#include "gtest/gtest.h"
#include "symboltable.h"
#include "exceptions/symbolnotfoundexception.h"
#include <string>
#include <exceptions/symbolalreadyexistsexception.h>
#include <exceptions/symbolinvalidexception.h>

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
    ASSERT_FALSE(SymbolTable::isValidSymbol("*N1"));
}

TEST(SymbolTable_Symbol, should_throw_exception_when_label_invalid){
    auto *st = new SymbolTable();
    ASSERT_THROW(st->addSymbol("test test",1), SymbolInvalidException);
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

TEST(SymbolTable_Extern, external_symbol_address_should_always_be_0){
    auto *st = new SymbolTable();
    st->addExternSymbol("test");
    ASSERT_EQ(0, st->getSymbolAddress("test"));
}

TEST(SymbolTable_Extern, symbol_added_as_extern_should_be_extern){
    auto *st = new SymbolTable();
    st->addExternSymbol("test");
    ASSERT_EQ(true, st->isExternSymbol("test"));
}

TEST(SymbolTable_Extern, symbol_added_as_extern_should_be_extern_case_insen){
    auto *st = new SymbolTable();
    st->addExternSymbol("test");
    ASSERT_EQ(true, st->isExternSymbol("TesT"));
}

TEST(SymbolTable_Public, should_be_able_to_check_if_symbol_is_public){
    auto *st = new SymbolTable();
    st->addSymbol("test", 1);
    ASSERT_FALSE(st->isPublicSymbol("test"));
}

TEST(SymbolTable_Public, should_be_able_to_set_symbol_as_public){
    auto *st = new SymbolTable();
    st->addSymbol("test", 1);
    st->setPublicSymbol("test");
    ASSERT_TRUE(st->isPublicSymbol("test"));
}

TEST(SymbolTable_Public, set_non_existing_symbol_as_public_should_throw){
    auto *st = new SymbolTable();
    ASSERT_THROW(st->setPublicSymbol("test"), SymbolNotFoundException);
}

TEST(SymbolTable_Public, check_public_on_non_existing_symbol_should_throw){
    auto *st = new SymbolTable();
    ASSERT_THROW(st->isPublicSymbol("test"), SymbolNotFoundException);
}

TEST(SymbolTable_Extern, check_extern_on_non_existing_symbol_should_throw){
    auto *st = new SymbolTable();
    ASSERT_THROW(st->isExternSymbol("test"), SymbolNotFoundException);
}

TEST(SymbolTable_Extern, symbol_not_added_as_extern_should_not_be_extern){
    auto *st = new SymbolTable();
    st->addSymbol("test", 1);
    ASSERT_EQ(false, st->isExternSymbol("test"));
}

TEST(SymbolTable_Symbol_, may_get_symbol_address){
    auto *s = new SymbolData(1);
    ASSERT_EQ(1, s->getAddress());
}

TEST(SymbolTable_Symbol_, may_check_if_symbol_is_extern){
    auto *s = new SymbolData(1, true);
    ASSERT_TRUE(s->isExternSymbol());
}

TEST(SymbolTable_Symbol_, may_check_if_symbol_is_extern_by_default){
    auto *s = new SymbolData(1);
    ASSERT_FALSE(s->isExternSymbol());
}

TEST(SymbolTable_Symbol_, may_check_if_symbol_is_public_by_default){
    auto *s = new SymbolData(1);
    ASSERT_FALSE(s->isPublicSymbol());
}

TEST(SymbolTable_Symbol_, may_set_symbol_as_public){
    auto *s = new SymbolData(1);
    s->setPublic();
    ASSERT_TRUE(s->isPublicSymbol());
}

TEST(SymbolTable_Public, may_get_public_symbols){
    auto *s = new SymbolTable();
    s->addSymbol("s",0);
    s->addSymbol("b",1);
    s->setPublicSymbol("S");
    s->setPublicSymbol("B");
    std::vector<std::string> publicSymbols;
    publicSymbols.insert(publicSymbols.end(), "b");
    publicSymbols.insert(publicSymbols.end(), "s");
    ASSERT_EQ(publicSymbols, s->getPublicSymbols());
}
