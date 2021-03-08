#include <string>
#include <vector>
#include <fstream>
#include <streambuf>
#include <firstpasser.h>
#include <secondpasser.h>
#include <iostream>

std::string readFile(const char *filename);
void printSecondPassErrors(std::vector<ParsingException> errors);

bool hasErrors(SecondPasser *second);

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Expected filename as single argument to executable!";
        return 1;
    }
    std::string content = readFile(argv[1]);

    auto first = new CodeFirstPasser(content);
    first->pass();

    auto second = new SecondPasser(first->getCodeLines(),
                                   first->getSymbolTable());
    second->pass();

    if (hasErrors(second))
        printSecondPassErrors(second->getErrors());
    else
        for (int i=0; i<second->getLineCount(); i++){
            auto pl = second->getProcessedLine(i);
            if (!pl.empty()) {
                std::cout << pl;
                if (i < (second->getLineCount() - 1))
                    std::cout << " ";
            }
        }

    return 0;
}

bool hasErrors(SecondPasser *second) {
    return second->getErrorCount() > 0;
}

void printSecondPassErrors(std::vector<ParsingException> errors) {
    for (auto &error : errors)
        std::cout << error.what() << std::endl;
}

std::string readFile(const char *filename) {
    std::ifstream t(filename);
    return std::string ((std::istreambuf_iterator<char>(t)),
                        std::istreambuf_iterator<char>());
}
