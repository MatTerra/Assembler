//
// Created by mateusberardo on 01/03/2021.
//
#include "gtest/gtest.h"
#include "firstpasser.h"
#include "symboltable.h"
#include "codeline.h"

TEST(FirstPasser, may_instantiate_first_passer){
    auto *fp = new FirstPasser("");
    ASSERT_TRUE(fp != nullptr);
}

TEST(FirstPasser, symbol_table_should_be_empty_before_pass){
    auto *fp = new FirstPasser("");
    ASSERT_EQ(0, fp->getSymbolCount());
}

TEST(FirstPasser_CodeLines, code_lines_should_be_empty){
    auto *fp = new FirstPasser("");
    ASSERT_EQ(std::vector<CodeLine>(), fp->getCodeLines());
}

TEST(FirstPasser_SymbolTable, should_have_symbol_table){
    auto *fp = new FirstPasser("");
    ASSERT_EQ(SymbolTable::getInstance(), fp->getSymbolTable());
}

TEST(FirstPasser_CodeLines, pass_should_generate_lines_vector){
    std::string lines = "start: add 8 ; simple add";
    auto *cl = new CodeLine(lines);
    auto codeLines = std::vector<CodeLine>();
    codeLines.insert(codeLines.cend(), *cl);
    auto *fp = new FirstPasser(lines);
    fp->pass();
    ASSERT_EQ(codeLines, fp->getCodeLines());
}

TEST(FirstPasser_CodeLines, pass_should_generate_lines_vector_with_multiple_lines){
    std::string lines = "start: add 8 ; simple add\n  stop\nok: CONST 1";
    auto *cl = new CodeLine("start: add 8 ; simple add");
    auto *cl2 = new CodeLine("  stop");
    auto *cl3 = new CodeLine("ok: CONST 1");
    auto codeLines = std::vector<CodeLine>();
    codeLines.insert(codeLines.cend(), *cl);
    codeLines.insert(codeLines.cend(), *cl2);
    codeLines.insert(codeLines.cend(), *cl3);
    auto *fp = new FirstPasser(lines);
    fp->pass();
    ASSERT_EQ(codeLines, fp->getCodeLines());
}

TEST(FirstPasser_ShouldGenerateSymbolTable, pass_should_register_all_symbols){
    std::string lines = "start: add 8 ; simple add\n  stop\nok: CONST 1";
    auto *fp = new FirstPasser(lines);
    fp->pass();
    auto *st = SymbolTable::getInstance();
    ASSERT_EQ(0, st->getSymbolAddress("start"));
    ASSERT_EQ(3, st->getSymbolAddress("ok"));
    delete st;
}
