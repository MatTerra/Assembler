//
// Created by mateusberardo on 02/05/2021.
//
#include "gtest/gtest.h"
#include "programchecker.h"
#include <string>

TEST(ProgramChecker, may_check_without_instantiating){
    std::string module = "\nsection data\nsection text\nstart: stop\n";
    ASSERT_TRUE(ProgramChecker::check(module));
}

TEST(ProgramChecker, should_be_invalid_if_end){
    std::string module = "section data\nsection text\nstart: stop\nEND";
    ASSERT_FALSE(ProgramChecker::check(module));
}

TEST(ProgramChecker, should_be_invalid_if_begin){
    std::string module = "begin\nsection data\nsection text\nstart: stop";
    ASSERT_FALSE(ProgramChecker::check(module));
}

TEST(ProgramChecker, should_be_invalid_if_begin_and_end){
    std::string module = "begin\nsection data\nsection text\nstart: stop\nEND";
    ASSERT_FALSE(ProgramChecker::check(module));
}