//
// Created by mateusberardo on 05/03/2021.
//

#include "gtest/gtest.h"
#include "parsingerrors/undefinedsymbolerror.h"
#include "parsingerrors/unknownoperationerror.h"
#include "parsingerrors/invalidoperandcounterror.h"

TEST(UndefinedSymbolException, what_shoud_describe_error){
    auto *exc = new UndefinedSymbolError(1, "ok");
    ASSERT_EQ("Semantic Error: Undefined symbol \"ok\" in line 1.", exc->what());
}

TEST(UnknowOperationException, what_shoud_describe_error){
    auto *exc = new UnknownOperationError(1, "ok");
    ASSERT_EQ("Lexical Error: Unknown mnemonic \"ok\" in line 1.", exc->what());
}

TEST(InvalidOperandCount, what_shoud_describe_error){
    auto *exc = new InvalidOperandCountError(1, "add");
    ASSERT_EQ("Semantic Error: Invalid operand count for operation \"add\" in line 1.",
              exc->what());
}

