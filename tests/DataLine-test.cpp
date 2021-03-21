//
// Created by mateusberardo on 26/02/2021.
//
#include "gtest/gtest.h"
#include "dataline.h"
#include <string>
#include <exceptions/operationnotfoundexception.h>

TEST(DataLine, may_instantiate_dataline){
    auto *dl = new DataLine(";blank line");
    ASSERT_NE(nullptr, dl);
}

TEST(DataLine, should_have_raw_line){
    auto *dl = new DataLine("label: space; with a comment");
    ASSERT_EQ("label: space; with a comment", dl->getRawLine());
}

TEST(DataLine_Label, should_get_label){
    auto *dl = new DataLine("label:");
    ASSERT_EQ("label", dl->getLabel());
}

TEST(DataLine_Label, label_should_be_empty_if_no_label){
    auto *dl = new DataLine("const 8");
    ASSERT_EQ("", dl->getLabel());
}

TEST(DataLine_Label, should_have_label){
    auto *dl = new DataLine("label:");
    ASSERT_TRUE(dl->hasLabel());
}

TEST(DataLine_Label, shouldnt_have_label){
    auto *dl = new DataLine("CONST 8 ; comment");
    ASSERT_FALSE(dl->hasLabel());
}

TEST(DataLine_Label, should_remove_whitespaces_before_label){
    auto *dl = new DataLine("       label:");
    ASSERT_EQ("label", dl->getLabel());
}

TEST(DataLine_Label, should_get_first_label){
    auto *dl = new DataLine("label:label2: CONST 8 ; just a comment ;;");
    ASSERT_EQ("label", dl->getLabel());
}

TEST(DataLine_Mnemonic, should_get_correct_mnemonic){
    auto *dl = new DataLine("label:label2: space ; just a comment ;;");
    ASSERT_EQ("space", dl->getOperationMnemonic());
}

TEST(DataLine_Mnemonic, should_get_correct_mnemonic_with_colon_on_comment){
    auto *dl = new DataLine("label:label2: const 8 ; just a comment: to make it fail ;;");
    ASSERT_EQ("const", dl->getOperationMnemonic());
}

TEST(DataLine_Comment, should_have_comment){
    auto *dl = new DataLine("; Just a comment");
    ASSERT_TRUE(dl->hasComment());
}

TEST(DataLine_Comment, shouldnt_have_comment){
    auto *dl = new DataLine("cool_label: space 8");
    ASSERT_FALSE(dl->hasComment());
}

TEST(DataLine_Comment, should_get_comment){
    auto *dl = new DataLine("; with comment");
    ASSERT_EQ(" with comment", dl->getComment());
}

TEST(DataLine_Operation, should_have_operation){
    auto *dl = new DataLine("label: space 8 ; Comment");
    ASSERT_TRUE(dl->hasOperation());
}

TEST(DataLine_Operation, shouldnt_have_operation){
    auto *dl = new DataLine("label:      ; Comment");
    ASSERT_FALSE(dl->hasOperation());
}

TEST(DataLine_Value, shouldnt_have_operation){
    auto *dl = new DataLine("label:      ; Comment");
    ASSERT_EQ(0, dl->getValue());
}

TEST(DataLine_Operation, should_get_operation_mnemonic){
    auto *dl = new DataLine("label:     space  8 ; Comment");
    ASSERT_EQ("space", dl->getOperationMnemonic());
}

TEST(DataLine_Value, should_get_value_space){
    auto *dl = new DataLine("label:     space  8 ; Comment");
    ASSERT_EQ(0, dl->getValue());
}

TEST(DataLine_Value, should_get_value_const){
    auto *dl = new DataLine("label:     const -1 ; Comment");
    ASSERT_EQ(-1, dl->getValue());
}

TEST(DataLine_Value, should_get_value_not_valid){
    auto *dl = new DataLine("label:     const -1 ; Comment");
    ASSERT_EQ(-1, dl->getValue());
}

TEST(DataLine_Operation, should_get_operation_spacer_size){
    auto *dl = new DataLine("label:     space; Comment");
    ASSERT_EQ(1, dl->getAddressSize());
}

TEST(DataLine_Operation, should_get_operation_spacer_size_1){
    auto *dl = new DataLine("label:     const 8 ; Comment");
    ASSERT_EQ(1, dl->getAddressSize());
}

TEST(DataLine_Operation, should_get_operation_spacer_size_0){
    auto *dl = new DataLine("label:     ; Comment");
    ASSERT_EQ(0, dl->getAddressSize());
}

TEST(DataLine_Mnemonic, operation_should_be_empty_if_none){
    auto *dl = new DataLine("label:     ; Comment");
    ASSERT_EQ("", dl->getOperationMnemonic());
}

TEST(DataLine_Mnemonic, operation_should_be_empty_if_none_no_spaces){
    auto *dl = new DataLine("label:; Comment");
    ASSERT_EQ("", dl->getOperationMnemonic());
}

TEST(DataLine_Operand, should_get_operands){
    auto *dl = new DataLine("label:     const -8 ; Comment");
    auto result = std::vector<std::string>();
    result.insert(result.cend(), "-8");
    ASSERT_EQ(result, dl->getOperands());
}

TEST(DataLine_Operand, should_get_multiple_operands){
    auto *dl = new DataLine("label:     const  8     ,    7 ; Comment");
    auto result = std::vector<std::string>();
    result.insert(result.cend(), "8");
    result.insert(result.cend(), "7");
    ASSERT_EQ(result, dl->getOperands());
}

TEST(DataLine_Operand, should_get_multiple_operands_good_format){
    auto *dl = new DataLine("label:     const 8, 7 ; Comment");
    auto result = std::vector<std::string>();
    result.insert(result.cend(), "8");
    result.insert(result.cend(), "7");
    ASSERT_EQ(result, dl->getOperands());
}

TEST(DataLine_Operand, should_get_multiple_operands_no_space_after_comma){
    auto *dl = new DataLine(" const 8,7");
    auto result = std::vector<std::string>();
    result.insert(result.cend(), "8");
    result.insert(result.cend(), "7");
    ASSERT_EQ(result, dl->getOperands());
}

TEST(DataLine_Operand, should_have_operands){
    auto *dl = new DataLine("label:     const 8, 7 ; Comment");
    ASSERT_TRUE(dl->hasOperands());
}

TEST(DataLine_Operation, operation_should_be_null_if_mnemonic_wrong){
    auto dl = new DataLine("cons 6");
    ASSERT_EQ(nullptr, dl->getOperation());
}

TEST(DataLine_Operation, operation_should_be_null_if_operand_wrong){
    auto dl = new DataLine("const start");
    ASSERT_EQ(nullptr, dl->getOperation());
}

TEST(DataLine_Operand, should_be_empty_if_no_operands){
    auto *dl = new DataLine("end:     space ; final");
    auto result = std::vector<std::string>();
    ASSERT_EQ(result, dl->getOperands());
}

TEST(DataLine_Operand, shouldnt_have_operands_if_no_operands){
    auto *dl = new DataLine("end:     space ; final");
    ASSERT_FALSE(dl->hasOperands());
}

TEST(DataLine_Operand, should_be_valid_if_space_no_operand){
    auto *dl = new DataLine("end:     space ; final");
    ASSERT_TRUE(dl->isValid());
}

TEST(DataLine_Operand, should_be_invalid_if_space_has_operands){
    auto *dl = new DataLine("end:     space 1 ; final");
    ASSERT_FALSE(dl->isValid());
}

TEST(DataLine_Operand, should_be_valid_if_const_one_operand){
    auto *dl = new DataLine("end:     const 2 ; final");
    ASSERT_TRUE(dl->isValid());
}

TEST(DataLine_Operand, should_be_invalid_if_const_two_operands){
    auto *dl = new DataLine("end:     const 1, 2 ; final");
    ASSERT_FALSE(dl->isValid());
}

TEST(DataLine_Operand, should_be_invalid_if_const_no_operands){
    auto *dl = new DataLine("end:     const  ; final");
    ASSERT_FALSE(dl->isValid());
}

TEST(DataLine_Operand, should_be_valid_if_no_operation){
    auto *dl = new DataLine("end:     ; final");
    ASSERT_TRUE(dl->isValid());
}

TEST(DataLine_Operand, should_be_invalid_if_operands_wrong){
    auto *dl = new DataLine("end:     const start; final");
    ASSERT_FALSE(dl->isValid());
}

TEST(DataLine_Operation, should_get_operation){
    auto *dl = new DataLine("end: const 8    ; final");
    ASSERT_NE(nullptr, dl->getOperation());
}

TEST(DataLine_equals, should_be_equal_if_raw_equals){
    auto dl = DataLine("end:     space ; final");
    auto dl2 = DataLine("end:     space ; final");
    ASSERT_TRUE(dl==dl2);
}