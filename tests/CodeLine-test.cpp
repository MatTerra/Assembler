//
// Created by mateusberardo on 26/02/2021.
//
#include "gtest/gtest.h"
#include "codeline.h"
#include <string>

TEST(CodeLine, may_instantiate_codeline){
    auto *cl = new CodeLine(";blank line");
    ASSERT_TRUE(cl != nullptr);
}

TEST(CodeLine, should_have_raw_line){
    auto *cl = new CodeLine("label: add 8 ; with a comment");
    ASSERT_EQ("label: add 8 ; with a comment", cl->getRawLine());
}

TEST(CodeLine_Label, should_get_label){
    auto *cl = new CodeLine("label:");
    ASSERT_EQ("label", cl->getLabel());
}

TEST(CodeLine_Label, should_get_label_with_space_just_before_colon){
    auto *cl = new CodeLine("label :");
    ASSERT_EQ("label", cl->getLabel());
}

TEST(CodeLine_Label, shouldnt_have_label_if_colon_in_comment){
    auto *cl = new CodeLine("label ; okok :");
    ASSERT_FALSE(cl->hasLabel());
}

TEST(CodeLine_Label, label_should_be_empty_if_no_label){
    auto *cl = new CodeLine("add 8");
    ASSERT_EQ("", cl->getLabel());
}

TEST(CodeLine_Label, should_have_label){
    auto *cl = new CodeLine("label:");
    ASSERT_TRUE(cl->hasLabel());
}

TEST(CodeLine_Label, shouldnt_have_label){
    auto *cl = new CodeLine("add 8 ; comment");
    ASSERT_FALSE(cl->hasLabel());
}

TEST(CodeLine_Label, should_remove_whitespaces_before_label){
    auto *cl = new CodeLine("       label:");
    ASSERT_EQ("label", cl->getLabel());
}

TEST(CodeLine_Label, should_get_first_label){
    auto *cl = new CodeLine("label:label2: add 8 ; just a comment ;;");
    ASSERT_EQ("label", cl->getLabel());
}

TEST(CodeLine_Mnemonic, should_get_correct_mnemonic){
    auto *cl = new CodeLine("label:label2: add 8 ; just a comment ;;");
    ASSERT_EQ("add", cl->getOperationMnemonic());
}
TEST(CodeLine_Mnemonic, should_get_correct_mnemonic_with_colon_on_comment){
    auto *cl = new CodeLine("label:label2: add 8 ; just a comment: to make it fail ;;");
    ASSERT_EQ("add", cl->getOperationMnemonic());
}

TEST(CodeLine_Comment, should_have_comment){
    auto *cl = new CodeLine("; Just a comment");
    ASSERT_TRUE(cl->hasComment());
}

TEST(CodeLine_Comment, shouldnt_have_comment){
    auto *cl = new CodeLine("cool_label: add 8");
    ASSERT_FALSE(cl->hasComment());
}

TEST(CodeLine_Comment, should_get_comment){
    auto *cl = new CodeLine("; with comment");
    ASSERT_EQ(" with comment", cl->getComment());
}

TEST(CodeLine_Operation, should_have_operation){
    auto *cl = new CodeLine("label: add 8 ; Comment");
    ASSERT_TRUE(cl->hasOperation());
}

TEST(CodeLine_Operation, shouldnt_have_operation){
    auto *cl = new CodeLine("label:      ; Comment");
    ASSERT_FALSE(cl->hasOperation());
}

TEST(CodeLine_Operation, operation_should_be_null){
    auto *cl = new CodeLine("label:      ; Comment");
    ASSERT_EQ(nullptr, cl->getOperation());
}

TEST(CodeLine_Operation, should_get_operation_mnemonic){
    auto *cl = new CodeLine("label:     add  8 ; Comment");
    ASSERT_EQ("add", cl->getOperationMnemonic());
}

TEST(CodeLine_Operation, should_get_operation){
    auto *cl = new CodeLine("label:     add  8 ; Comment");
    ASSERT_TRUE(cl->getOperation() != nullptr);
    ASSERT_EQ("add", cl->getOperation()->getOperation());
}

TEST(CodeLine_Operation, should_get_operation_addr_size_2){
    auto *cl = new CodeLine("label:     add  8 ; Comment");
    ASSERT_EQ(2, cl->getAddressSize());
}

TEST(CodeLine_Operation, should_get_operation_addr_size_3){
    auto *cl = new CodeLine("label:     copy  8,3 ; Comment");
    ASSERT_EQ(3, cl->getAddressSize());
}


TEST(CodeLine_Operation, should_get_operation_addr_size_1){
    auto *cl = new CodeLine("label:     stop ; Comment");
    ASSERT_EQ(1, cl->getAddressSize());
}

TEST(CodeLine_Operation, should_get_operation_addr_size_0){
    auto *cl = new CodeLine("label:     ; Comment");
    ASSERT_EQ(0, cl->getAddressSize());
}

TEST(CodeLine_Operation, operation_should_be_empty_if_none){
    auto *cl = new CodeLine("label:     ; Comment");
    ASSERT_EQ("", cl->getOperationMnemonic());
}

TEST(CodeLine_Operation, operation_should_be_empty_if_none_no_spaces){
    auto *cl = new CodeLine("label:; Comment");
    ASSERT_EQ("", cl->getOperationMnemonic());
}

TEST(CodeLine_Operation, get_op_code_should_return_string_for_opcode){
    auto *cl = new CodeLine("label: stop; Comment");
    ASSERT_EQ("14", cl->getOpCode());
}

TEST(CodeLine_Operation, get_op_code_should_return_empty_string_if_no_operation){
    auto *cl = new CodeLine("label: ; Comment");
    ASSERT_EQ("", cl->getOpCode());
}

TEST(CodeLine_Operand, should_get_operands){
    auto *cl = new CodeLine("label:     add  8 ; Comment");
    auto result = std::vector<std::string>();
    result.insert(result.cend(), "8");
    ASSERT_EQ(result, cl->getOperands());
}

TEST(CodeLine_Operand, should_get_multiple_operands){
    auto *cl = new CodeLine("label:     copy  8     ,    7 ; Comment");
    auto result = std::vector<std::string>();
    result.insert(result.cend(), "8");
    result.insert(result.cend(), "7");
    ASSERT_EQ(result, cl->getOperands());
}

TEST(CodeLine_Operand, should_get_multiple_operands_good_format){
    auto *cl = new CodeLine("label:     copy 8, 7 ; Comment");
    auto result = std::vector<std::string>();
    result.insert(result.cend(), "8");
    result.insert(result.cend(), "7");
    ASSERT_EQ(result, cl->getOperands());
}

TEST(CodeLine_Operand, should_get_multiple_operands_no_space_after_comma){
    auto *cl = new CodeLine(" copy 8,7");
    auto result = std::vector<std::string>();
    result.insert(result.cend(), "8");
    result.insert(result.cend(), "7");
    ASSERT_EQ(result, cl->getOperands());
}

TEST(CodeLine_Operand, should_have_operands){
    auto *cl = new CodeLine("label:     copy 8, 7 ; Comment");
    ASSERT_TRUE(cl->hasOperands());
}

TEST(CodeLine_Operand, should_be_empty_if_no_operands){
    auto *cl = new CodeLine("end:     stop ; final");
    auto result = std::vector<std::string>();
    ASSERT_EQ(result, cl->getOperands());
}

TEST(CodeLine_Operand, shouldnt_have_operands_if_no_operands){
    auto *cl = new CodeLine("end:     stop ; final");
    ASSERT_FALSE(cl->hasOperands());
}

TEST(CodeLine_equals, should_be_equal_if_raw_equals){
    auto cl = CodeLine("end:     stop ; final");
    auto cl2 = CodeLine("end:     stop ; final");
    ASSERT_TRUE(cl==cl2);
}