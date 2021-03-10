#include <string>
#include <vector>
#include <fstream>
#include <streambuf>
#include <codefirstpasser.h>
#include <secondpasser.h>
#include <iostream>
#include <sectionextractor.h>
#include <datafirstpasser.h>
#include <iomanip>

std::string readFile(const char *filename);
void printErrors(std::vector<ParsingError> errors);

bool hasErrors(SecondPasser *second);
bool hasErrors(DataFirstPasser *passer);

void outputAssembledInstructions(std::ostream &output, SecondPasser *second);

void outputAssembledData(std::ostream &output, DataFirstPasser *data);

void printAllErrors(DataFirstPasser *data, SecondPasser *second);

void outputAssembledProgram(std::ostream &output, DataFirstPasser *data,
                            SecondPasser *second);

SecondPasser * makeSecondPass(CodeFirstPasser *first, long lineOffset);

DataFirstPasser *makeDataPass(SectionExtractor *extractor,
                              SymbolTable *symbolTable,
                              uint16_t finalAddress);

CodeFirstPasser *makeTextPass(SectionExtractor *extractor);

void makeFirstPass(SectionExtractor *extractor, CodeFirstPasser *&first,
                   DataFirstPasser *&data);

int main(int argc, char **argv) {
    std::ostream &output = std::cout;
    if (argc != 2) {
        std::cout << "Expected filename as single argument to executable!";
        return 1;
    }

    auto extractor = new SectionExtractor(readFile(argv[1]));

    CodeFirstPasser *first;
    DataFirstPasser *data;
    makeFirstPass(extractor, first, data);

    auto second = makeSecondPass(first, extractor->getTextLineOffset());

    if (hasErrors(second) || hasErrors(data)) {
        printAllErrors(data, second);
        return 1;
    }

    outputAssembledProgram(output, data, second);

    return 0;
}

void makeFirstPass(SectionExtractor *extractor, CodeFirstPasser *&first,
                   DataFirstPasser *&data) {
    first = makeTextPass(extractor);
    data = makeDataPass(extractor, first->getSymbolTable(),
                        first->getFinalAddress());
}

CodeFirstPasser *makeTextPass(SectionExtractor *extractor) {
    auto first = new CodeFirstPasser(extractor->getTextSection());
    first->pass();
    return first;
}

DataFirstPasser *makeDataPass(SectionExtractor *extractor,
                              SymbolTable *symbolTable,
                              uint16_t finalAddress) {
    auto data = new DataFirstPasser(extractor->getDataSection(),
                                    symbolTable, finalAddress,
                                    extractor->getDataLineOffset());
    data->pass();
    return data;
}

SecondPasser * makeSecondPass(CodeFirstPasser *first, long lineOffset) {
    auto second = new SecondPasser(first->getCodeLines(),
                                   first->getSymbolTable(),
                                   lineOffset);
    second->pass();
    return second;
}

void outputAssembledProgram(std::ostream &output, DataFirstPasser *data,
                            SecondPasser *second) {
    outputAssembledInstructions(output, second);
    outputAssembledData(output, data);
}

void printAllErrors(DataFirstPasser *data, SecondPasser *second) {
    printErrors(data->getErrors());
    printErrors(second->getErrors());
}

void outputAssembledData(std::ostream &output, DataFirstPasser *data) {
    for (auto &dataLine : data->getDataLines())
        if (dataLine.hasOperation())
            output << " " << dataLine.getValue();
}

void outputAssembledInstructions(std::ostream &output, SecondPasser *second) {
    for (int i = 0; i < second->getLineCount(); i++) {
        auto pl = second->getProcessedLine(i);
        if (!pl.empty()) {
            output << pl;
            if (i < (second->getLineCount() - 2))
                output << " ";
        }
    }
}

bool hasErrors(SecondPasser *second) {
    return second->getErrorCount() > 0;
}

bool hasErrors(DataFirstPasser *passer) {
    return passer->getErrorCount() > 0;
}

void printErrors(std::vector<ParsingError> errors) {
    for (auto &error : errors)
        std::cout << error.what() << std::endl;
}

std::string readFile(const char *filename) {
    std::ifstream t(filename);
    return std::string ((std::istreambuf_iterator<char>(t)),
                        std::istreambuf_iterator<char>());
}
