//
// Created by mateusberardo on 05/03/2021.
//
#include <parsingerrors/undefinedsymbolerror.h>
#include <parsingerrors/unknownoperationerror.h>
#include <parsingerrors/invalidoperandcounterror.h>
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
    ASSERT_EQ(UndefinedSymbolError(1, "stop").what(),
              secondPasser->getErrors()[0].what());
}

TEST(SecondPasser, should_have_error_if_mnemonic_unknown){
    auto cl = std::vector<CodeLine>();
    cl.insert(cl.cbegin(), CodeLine("start: stp ; nothing to do"));
    auto sb = new SymbolTable();
    sb->addSymbol("start", 0);
    auto *secondPasser = new SecondPasser(cl, sb);
    secondPasser->pass();
    ASSERT_EQ(UnknownOperationError(1, "stp").what(),
              secondPasser->getErrors()[0].what());
}

TEST(SecondPasser, should_have_error_if_invalid_number_of_operands){
    auto cl = std::vector<CodeLine>();
    cl.insert(cl.cbegin(), CodeLine("start: JMP start, start; nothing to do"));
    auto sb = new SymbolTable();
    sb->addSymbol("start", 0);
    auto *secondPasser = new SecondPasser(cl, sb);
    secondPasser->pass();
    ASSERT_EQ(InvalidOperandCountError(1, "JMP").what(),
              secondPasser->getErrors()[0].what());
}

TEST(SecondPasser, error_should_consider_starting_line){
    auto cl = std::vector<CodeLine>();
    cl.insert(cl.cbegin(), CodeLine("start: JMP start, start; nothing to do"));
    auto sb = new SymbolTable();
    sb->addSymbol("start", 0);
    auto *secondPasser = new SecondPasser(cl, sb, 3);
    secondPasser->pass();
    ASSERT_EQ(InvalidOperandCountError(3, "JMP").what(),
              secondPasser->getErrors()[0].what());
}

TEST(SecondPasser, should_count_0_errors_if_ok){
    auto cl = std::vector<CodeLine>();
    cl.insert(cl.cbegin(), CodeLine("start: JMP start ; nothing to do"));
    auto sb = new SymbolTable();
    sb->addSymbol("start", 0);
    auto *secondPasser = new SecondPasser(cl, sb);
    secondPasser->pass();
    ASSERT_EQ(0,
              secondPasser->getErrorCount());
}

TEST(SecondPasser, should_be_able_to_count_errors){
    auto cl = std::vector<CodeLine>();
    cl.insert(cl.cbegin(), CodeLine("start: JMP start, start; nothing to do"));
    cl.insert(cl.cbegin(), CodeLine(" jmpnp start"));
    cl.insert(cl.cbegin(), CodeLine(" add ok"));
    auto sb = new SymbolTable();
    sb->addSymbol("start", 0);
    auto *secondPasser = new SecondPasser(cl, sb);
    secondPasser->pass();
    ASSERT_EQ(3,
              secondPasser->getErrorCount());
}

TEST(SecondPasser, should_be_able_to_count_multiple_errors_per_line){
    auto cl = std::vector<CodeLine>();
    cl.insert(cl.cbegin(), CodeLine("start: JMP start, ok; nothing to do"));
    cl.insert(cl.cbegin(), CodeLine(" jmpnp start"));
    cl.insert(cl.cbegin(), CodeLine(" add ok"));
    auto sb = new SymbolTable();
    sb->addSymbol("start", 0);
    auto *secondPasser = new SecondPasser(cl, sb);
    secondPasser->pass();
    ASSERT_EQ(4,
              secondPasser->getErrorCount());
}

TEST(SecondPasser, should_be_able_to_generate_multiple_errors_per_line){
    auto cl = std::vector<CodeLine>();
    cl.insert(cl.end(), CodeLine("start: JMP start, ok; nothing to do"));
    cl.insert(cl.end(), CodeLine(" jmpnp start"));
    cl.insert(cl.end(), CodeLine(" add ok"));
    auto sb = new SymbolTable();
    sb->addSymbol("start", 0);
    auto errors = std::vector<ParsingError>();
    errors.insert(errors.end(), InvalidOperandCountError(1, "JMP"));
    errors.insert(errors.end(), UndefinedSymbolError(1, "ok"));
    errors.insert(errors.end(), UnknownOperationError(2, "jmpnp"));
    errors.insert(errors.end(), UndefinedSymbolError(3, "ok"));
    auto *secondPasser = new SecondPasser(cl, sb);
    secondPasser->pass();
    for (int i = 0; i < secondPasser->getErrorCount(); i++)
        ASSERT_EQ(errors[i].what(),
                  secondPasser->getErrors()[i].what());
}

TEST(SecondPasser, should_count_1_line){
    auto cl = std::vector<CodeLine>();
    cl.insert(cl.cbegin(), CodeLine("start: JMP start ; nothing to do"));
    auto sb = new SymbolTable();
    sb->addSymbol("start", 0);
    auto *secondPasser = new SecondPasser(cl, sb);
    secondPasser->pass();
    ASSERT_EQ(1, secondPasser->getLineCount());
}

TEST(SecondPasser, should_be_able_to_count_3_lines_with_comments){
    auto cl = std::vector<CodeLine>();
    cl.insert(cl.cbegin(), CodeLine("start: JMP start; nothing to do"));
    cl.insert(cl.cbegin(), CodeLine(" ; just comment"));
    cl.insert(cl.cbegin(), CodeLine(" add start"));
    auto sb = new SymbolTable();
    sb->addSymbol("start", 0);
    auto *secondPasser = new SecondPasser(cl, sb);
    secondPasser->pass();
    ASSERT_EQ(3, secondPasser->getLineCount());
}

TEST(SecondPasser, should_be_able_to_parse_3_lines_independently){
    auto cl = std::vector<CodeLine>();
    cl.insert(cl.end(), CodeLine("start: JMP start; nothing to do"));
    cl.insert(cl.end(), CodeLine(" ; just comment"));
    cl.insert(cl.end(), CodeLine(" add start"));
    auto sb = new SymbolTable();
    sb->addSymbol("start", 0);
    auto *secondPasser = new SecondPasser(cl, sb);
    secondPasser->pass();
    ASSERT_EQ("05 00", secondPasser->getProcessedLine(0));
    ASSERT_EQ("", secondPasser->getProcessedLine(1));
    ASSERT_EQ("01 00", secondPasser->getProcessedLine(2));
}

TEST(SecondPasser, get_non_existent_line_shouldnt_crash){
    auto cl = std::vector<CodeLine>();
    cl.insert(cl.end(), CodeLine("end:      stop; nothing to do"));
    auto sb = new SymbolTable();
    sb->addSymbol("start", 0);
    auto *secondPasser = new SecondPasser(cl, sb);
    secondPasser->pass();
    ASSERT_EQ("", secondPasser->getProcessedLine(1));
}