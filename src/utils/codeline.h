//
// Created by mateusberardo on 26/02/2021.
//
#ifndef MONTADOR_CODELINE_H
#define MONTADOR_CODELINE_H

static const char *const whitespaces = " \t\r\f\v";

#include <string>
#include <utility>


class CodeLine {
public:
    explicit CodeLine(std::string line);
    bool hasLabel();
    bool hasComment();
    std::string getRawLine(){ return rawLine; };
    std::string getLabel(){ return label; };
    std::string getComment(){ return comment; };
    std::string getOperation(){ return operation; };

    bool hasOperation();
private:
    std::string rawLine;
    std::string label;
    std::string operation;
//    std::vector<std::string> operands;
    std::string comment;
    void extractLabel();
    void extractComment();

    static void removeLeadingWhitespaces(std::string &myString){
        myString.erase(0, myString.find_first_not_of(whitespaces));
    };

    std::string getRawOperation() const;

    void extractOperation();
};

#endif //MONTADOR_CODELINE_H
