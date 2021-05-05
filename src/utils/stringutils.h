//
// Created by mateusberardo on 28/02/2021.
//
#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <algorithm>
#include <fstream>

static const char *const whitespaces = " \t\r\f\v\n";

static void removeLeadingWhitespaces(std::string &myString){
    myString.erase(0, myString.find_first_not_of(whitespaces));
};
static void removeTrailingWhitespaces(std::string &myString){
    myString.erase(myString.find_last_not_of(whitespaces)+1);
};
static void trim(std::string &myString){
    removeLeadingWhitespaces(myString);
    removeTrailingWhitespaces(myString);
};
static void lowerCaseString(std::string &string) {
    std::transform(string.begin(), string.end(), string.begin(),
                   [](unsigned char c){ return tolower(c); });
}

static std::string readFile(std::string filename) {
    std::ifstream t(filename);
    return std::string ((std::istreambuf_iterator<char>(t)),
                        std::istreambuf_iterator<char>());
}
#endif
