//
// Created by mateusberardo on 05/03/2021.
//
#include <exceptions/undefinedsymbolexception.h>
#include <exceptions/unknownoperationexception.h>
#include <exceptions/invalidoperandcountexception.h>
#include "gtest/gtest.h"
#include "secondpasser.h"
#include "codeline.h"
#include "symboltable.h"

TEST(SecondPasser, may_instatiate_secondpasser){
    auto cl = std::vector<CodeLine>();
    auto sb = new SymbolTable();
    auto *secondPasser = new SecondPasser(cl, sb);
    ASSERT_NE(nullptr, secondPasser);
}

TEST(SecondPasser, should_generate_obj_code){
    auto cl = std::vector<CodeLine>();
    cl.insert(cl.cbegin(), CodeLine("start: ; nothing to do"));
    auto sb = new SymbolTable();
    auto *secondPasser = new SecondPasser(cl, sb);
    secondPasser->pass();
    ASSERT_EQ("", secondPasser->getProcessedLine(0));
}

TEST(SecondPasser, should_generate_obj_code_with_opcode){
    auto cl = std::vector<CodeLine>();
    cl.insert(cl.cbegin(), CodeLine("start: stop; nothing to do"));
    auto sb = new SymbolTable();
    auto *secondPasser = new SecondPasser(cl, sb);
    secondPasser->pass();
    ASSERT_EQ("14", secondPasser->getProcessedLine(0));
}

TEST(SecondPasser, should_generate_obj_code_with_operands){
    auto cl = std::vector<CodeLine>();
    cl.insert(cl.cbegin(), CodeLine("start: JMP start; nothing to do"));
    auto sb = new SymbolTable();
    sb->addSymbol("start", 0);
    auto *secondPasser = new SecondPasser(cl, sb);
    secondPasser->pass();
    ASSERT_EQ("05 00", secondPasser->getProcessedLine(0));
}

TEST(SecondPasser, should_have_error_if_symbol_not_found){
    auto cl = std::vector<CodeLine>();
    cl.insert(cl.cbegin(), CodeLine("start: JMP stop; nothing to do"));
    auto sb = new SymbolTable();
    sb->addSymbol("start", 0);
    auto *secondPasser = new SecondPasser(cl, sb);
    secondPasser->pass();
    ASSERT_EQ(UndefinedSymbolException(1, "stop").what(),
              secondPasser->getErrors()[0].what());
}

TEST(SecondPasser, should_have_error_if_mnemonic_unknown){
    auto cl = std::vector<CodeLine>();
    cl.insert(cl.cbegin(), CodeLine("start: stp ; nothing to do"));
    auto sb = new SymbolTable();
    sb->addSymbol("start", 0);
    auto *secondPasser = new SecondPasser(cl, sb);
    secondPasser->pass();
    ASSERT_EQ(UnknownOperationException(1, "stp").what(),
              secondPasser->getErrors()[0].what());
}

TEST(SecondPasser, should_have_error_if_invalid_number_of_operands){
    auto cl = std::vector<CodeLine>();
    cl.insert(cl.cbegin(), CodeLine("start: JMP start, start; nothing to do"));
    auto sb = new SymbolTable();
    sb->addSymbol("start", 0);
    auto *secondPasser = new SecondPasser(cl, sb);
    secondPasser->pass();
    ASSERT_EQ(InvalidOperandCountException(1,"JMP").what(),
              secondPasser->getErrors()[0].what());
}

TEST(SecondPasser, error_should_consider_starting_line){
    auto cl = std::vector<CodeLine>();
    cl.insert(cl.cbegin(), CodeLine("start: JMP start, start; nothing to do"));
    auto sb = new SymbolTable();
    sb->addSymbol("start", 0);
    auto *secondPasser = new SecondPasser(cl, sb, 3);
    secondPasser->pass();
    ASSERT_EQ(InvalidOperandCountException(3,"JMP").what(),
              secondPasser->getErrors()[0].what());
}