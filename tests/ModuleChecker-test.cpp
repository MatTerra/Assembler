//
// Created by mateusberardo on 02/05/2021.
//
#include "gtest/gtest.h"
#include "modulechecker.h"
#include <string>

TEST(ModuleChecker, may_check_without_instantiating){
    std::string module = "mod_a:BEGIN\nsection data\nsection text\nstart: stop\nEND";
    ASSERT_TRUE(ModuleChecker::check(module));
}

TEST(ModuleChecker, should_be_invalid_if_no_begin){
    std::string module = "section data\nsection text\nstart: stop\nEND";
    ASSERT_FALSE(ModuleChecker::check(module));
}

TEST(ModuleChecker, should_be_invalid_if_no_end){
    std::string module = "begin\nsection data\nsection text\nstart: stop";
    ASSERT_FALSE(ModuleChecker::check(module));
}