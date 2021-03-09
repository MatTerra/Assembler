//
// Created by mateusberardo on 08/03/2021.
//
#include "gtest/gtest.h"
#include "datafirstpasser.h"
#include "dataline.h"

TEST(DataFirstPasser, may_instantiate_first_passer){
    auto *fp = new DataFirstPasser("", new SymbolTable());
    ASSERT_TRUE(fp != nullptr);
}

TEST(DataFirstPasser, symbol_table_should_be_empty_before_pass){
    auto *fp = new DataFirstPasser("", new SymbolTable());
    ASSERT_EQ(0, fp->getSymbolCount());
}

TEST(DataFirstPasser_DataLines, data_lines_should_be_empty){
    auto *fp = new DataFirstPasser("", new SymbolTable());
    ASSERT_EQ(std::vector<DataLine>(), fp->getDataLines());
}

TEST(DataFirstPasser_SymbolTable, should_have_symbol_table){
    auto *fp = new DataFirstPasser("", new SymbolTable());
    ASSERT_NE(nullptr, fp->getSymbolTable());
}

TEST(DataFirstPasser_DataLines, pass_should_generate_data_lines_vector){
    std::string lines = "start: const 8 ; simple const";
    auto *cl = new DataLine(lines);
    auto dataLines = std::vector<DataLine>();
    dataLines.insert(dataLines.cend(), *cl);
    auto *fp = new DataFirstPasser(lines, new SymbolTable());
    fp->pass();
    ASSERT_EQ(dataLines, fp->getDataLines());
}

TEST(DataFirstPasser_DataLines, pass_should_generate_data_lines_vector_with_multiple_data_lines){
    std::string lines = "start: const 8 ; simple const\n  ;stop\nok: CONST 1";
    auto *cl = new DataLine("start: const 8 ; simple const");
    auto *cl2 = new DataLine("  ;stop");
    auto *cl3 = new DataLine("ok: CONST 1");
    auto dataLines = std::vector<DataLine>();
    dataLines.insert(dataLines.cend(), *cl);
    dataLines.insert(dataLines.cend(), *cl2);
    dataLines.insert(dataLines.cend(), *cl3);
    auto *fp = new DataFirstPasser(lines, new SymbolTable());
    fp->pass();
    ASSERT_EQ(dataLines, fp->getDataLines());
}

TEST(DataFirstPasser_ShouldGenerateSymbolTable, pass_should_register_all_symbols){
    std::string lines = "start: const 8 ; simple const\n  space\nok: CONST 1";
    auto *fp = new DataFirstPasser(lines, new SymbolTable());
    fp->pass();
    auto *st = fp->getSymbolTable();
    ASSERT_EQ(0, st->getSymbolAddress("start"));
    ASSERT_EQ(2, st->getSymbolAddress("ok"));
}

TEST(DataFirstPasser_ShouldGenerateSymbolTable, symbol_should_consider_starting_address){
    std::string lines = "start: const 8 ; simple const\n  space\nok: CONST 1";
    auto *fp = new DataFirstPasser(lines, new SymbolTable(), 2);
    fp->pass();
    auto *st = fp->getSymbolTable();
    ASSERT_EQ(2, st->getSymbolAddress("start"));
    ASSERT_EQ(4, st->getSymbolAddress("ok"));
}
