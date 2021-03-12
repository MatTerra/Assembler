//
// Created by mateusberardo on 05/03/2021.
//

#include <parsingerrors/symbolredefinederror.h>
#include <parsingerrors/invalidlabelerror.h>
#include <parsingerrors/invalidoperanderror.h>
#include "gtest/gtest.h"
#include "parsingerrors/undefinedsymbolerror.h"
#include "parsingerrors/unknownoperationerror.h"
#include "parsingerrors/invalidoperandcounterror.h"

TEST(UndefinedSymbolError, what_shoud_describe_error){
    auto *exc = new UndefinedSymbolError(1, "ok");
    ASSERT_EQ("Semantic Error: Undefined symbol \"ok\" in line 1.", exc->what());
}

TEST(UnknowOperationError, what_shoud_describe_error){
    auto *exc = new UnknownOperationError(1, "ok");
    ASSERT_EQ("Lexical Error: Unknown mnemonic \"ok\" in line 1.", exc->what());
}

TEST(InvalidOperandCountError, what_shoud_describe_error){
    auto *exc = new InvalidOperandCountError(1, "add");
    ASSERT_EQ("Semantic Error: Invalid operand count for operation \"add\" in line 1.",
              exc->what());
}

TEST(SymbolRedefinedError, what_shoud_describe_error){
    auto *exc = new SymbolRedefinedError(2, "add");
    ASSERT_EQ("Semantic Error: Redefinition of symbol \"add\" in line 2.",
              exc->what());
}

TEST(InvalidLabelError, what_shoud_describe_error){
    auto *exc = new InvalidLabelError(2, "label label");
    ASSERT_EQ("Syntax Error: Invalid label \"label label\" in line 2.",
              exc->what());
}

TEST(InvalidOperandError, what_shoud_describe_error){
    auto *exc = new InvalidOperandError(2, "3");
    ASSERT_EQ("Semantic Error: Invalid operand \"3\" in line 2.",
              exc->what());
}

