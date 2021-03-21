//
// Created by mateusberardo on 01/03/2021.
//
#include <parsingerrors/symbolredefinederror.h>
#include <parsingerrors/invalidlabelerror.h>
#include "gtest/gtest.h"
#include "passers/codefirstpasser.h"
#include "codeline.h"

TEST(CodeFirstPasser, may_instantiate_first_passer){
    auto *fp = new CodeFirstPasser("");
    ASSERT_TRUE(fp != nullptr);
}

TEST(CodeFirstPasser, symbol_table_should_be_empty_before_pass){
    auto *fp = new CodeFirstPasser("");
    ASSERT_EQ(0, fp->getSymbolCount());
}

TEST(FirstPasser_CodeLines, code_lines_should_be_empty){
    auto *fp = new CodeFirstPasser("");
    ASSERT_EQ(std::vector<CodeLine>(), fp->getCodeLines());
}

TEST(FirstPasser_SymbolTable, should_have_symbol_table){
    auto *fp = new CodeFirstPasser("");
    ASSERT_NE(nullptr, fp->getSymbolTable());
}

TEST(FirstPasser_CodeLines, pass_should_generate_code_lines_vector){
    std::string lines = "start: add 8 ; simple add";
    auto *cl = new CodeLine(lines);
    auto codeLines = std::vector<CodeLine>();
    codeLines.insert(codeLines.cend(), *cl);
    auto *fp = new CodeFirstPasser(lines);
    fp->pass();
    ASSERT_EQ(codeLines, fp->getCodeLines());
}

TEST(FirstPasser_CodeLines, should_get_final_address){
    std::string lines = "start: add 8 ; simple add";
    auto *fp = new CodeFirstPasser(lines);
    fp->pass();
    ASSERT_EQ(2, fp->getFinalAddress());
}

TEST(FirstPasser_CodeLines, pass_should_generate_code_lines_vector_with_multiple_code_lines){
    std::string lines = "start: add 8 ; simple add\n  stop\nok: jmp start";
    auto *cl = new CodeLine("start: add 8 ; simple add");
    auto *cl2 = new CodeLine("  stop");
    auto *cl3 = new CodeLine("ok: jmp start");
    auto codeLines = std::vector<CodeLine>();
    codeLines.insert(codeLines.cend(), *cl);
    codeLines.insert(codeLines.cend(), *cl2);
    codeLines.insert(codeLines.cend(), *cl3);
    auto *fp = new CodeFirstPasser(lines);
    fp->pass();
    ASSERT_EQ(codeLines, fp->getCodeLines());
}

TEST(FirstPasser_ShouldGenerateSymbolTable, pass_should_register_all_symbols){
    std::string lines = "start: add 8 ; simple add\n  stop\nok: jmp start";
    auto fp = new CodeFirstPasser(lines);
    fp->pass();
    auto *st = fp->getSymbolTable();
    ASSERT_EQ(0, st->getSymbolAddress("start"));
    ASSERT_EQ(3, st->getSymbolAddress("ok"));
}

TEST(FirstPasser, should_generate_correct_addresses){
    auto lines="start:      add     one                 ; Simple add something\njmp     end\n; Let's finish this empty file\nend:        stop";
    auto fp = new CodeFirstPasser(lines);
    fp->pass();
    auto *st = fp->getSymbolTable();
    ASSERT_EQ(0, st->getSymbolAddress("start"));
    ASSERT_EQ(4, st->getSymbolAddress("end"));
    ASSERT_EQ(5, fp->getFinalAddress());
}

TEST(FirstPasser, should_count_0_errors_if_ok){
    auto *firstPasser = new CodeFirstPasser("start: add 8 ; simple add\nstop");
    firstPasser->pass();
    ASSERT_EQ(0, firstPasser->getErrorCount());
}

TEST(FirstPasser, should_count_errors_if_not_ok){
    auto *firstPasser = new CodeFirstPasser("start: add 8 ; simple add\nstart: stop");
    firstPasser->pass();
    ASSERT_EQ(1, firstPasser->getErrorCount());
}

TEST(FirstPasser, should_have_error_if_symbol_redefined){
    auto *firstPasser = new CodeFirstPasser("start: add 8 ; simple add\nstart: stop");
    firstPasser->pass();
    ASSERT_EQ(SymbolRedefinedError(2, "start").what(),
              firstPasser->getErrors()[0].what());
}

TEST(FirstPasser, should_have_error_if_symbol_redefined_2){
    auto *firstPasser = new CodeFirstPasser("adding_one: add just_single_data\nADDING_one: add just_single_data\n;\n; This label was redefined\nstop\n");
    firstPasser->pass();
    ASSERT_EQ(SymbolRedefinedError(2, "adding_one").what(),
              firstPasser->getErrors()[0].what());
}

TEST(FirstPasser, should_have_error_if_label_invalid){
    auto *firstPasser = new CodeFirstPasser("start start: add 8 ; simple add\nstart: stop");
    firstPasser->pass();
    ASSERT_EQ(InvalidLabelError(1, "start start").what(),
              firstPasser->getErrors()[0].what());
}

TEST(FirstPasser, error_should_consider_starting_line){
    auto *firstPasser = new CodeFirstPasser("start: add 8 ; simple add\nstart: stop", 2);
    firstPasser->pass();
    ASSERT_EQ(SymbolRedefinedError(3, "start").what(),
              firstPasser->getErrors()[0].what());
}
TEST(FirstPasser, shouldnt_skip_newlines){
    auto *firstPasser = new CodeFirstPasser("start:\n\n; Starting the code now\n\nstart: load start", 11);
    firstPasser->pass();
    ASSERT_EQ(SymbolRedefinedError(15, "start").what(),
              firstPasser->getErrors()[0].what());
}
