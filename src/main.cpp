#include <string>
#include <vector>
#include <fstream>
#include <passers/codefirstpasser.h>
#include <passers/secondpasser.h>
#include <sectionextractor.h>
#include <passers/datafirstpasser.h>

std::string readFile(std::string filename);
void printErrors(std::vector<ParsingError> errors);

bool hasErrors(SecondPasser *second);
bool hasErrors(CodeFirstPasser *passer);
bool hasErrors(DataFirstPasser *passer);

void outputAssembledInstructions(std::ofstream &output, SecondPasser *second);

void outputAssembledData(std::ofstream &output, DataFirstPasser *data);

void printAllErrors(DataFirstPasser *data,
                    CodeFirstPasser *first, SecondPasser *second);

void outputAssembledProgram(std::ofstream &output, DataFirstPasser *data,
                            SecondPasser *second);

SecondPasser * makeSecondPass(CodeFirstPasser *first, long lineOffset);

DataFirstPasser *makeDataPass(SectionExtractor *extractor,
                              SymbolTable *symbolTable,
                              uint16_t finalAddress);

CodeFirstPasser *makeTextPass(SectionExtractor *extractor);

void makeFirstPass(SectionExtractor *extractor, CodeFirstPasser *&first,
                   DataFirstPasser *&data);

void outputProgramHeader(std::ofstream &ofstream, std::string basicString,
                         DataFirstPasser *pPasser, SecondPasser *pPasser1);

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "Expected filename as single argument to executable!";
        return 1;
    }

    auto filename = std::string(argv[1]);

    auto extension = filename.substr(filename.find_last_of('.'));
    if (extension != ".asm"){
        std::cout << "Expected an .asm file!";
        return 1;
    }


    auto extractor = new SectionExtractor(readFile(filename));

    CodeFirstPasser *first;
    DataFirstPasser *data;
    makeFirstPass(extractor, first, data);

    auto second = makeSecondPass(first, extractor->getTextLineOffset());

    if (hasErrors(first) || hasErrors(second) || hasErrors(data)) {
        printAllErrors(data, first, second);
        return 1;
    }

    std::ofstream output;
    output.open(filename.substr(0, filename.find_last_of('.'))+".obj") ;
    outputProgramHeader(output, filename, data, second);
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
    auto first = new CodeFirstPasser(extractor->getTextSection(),
                                     extractor->getTextLineOffset());
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


void outputProgramHeader(std::ofstream &output, std::string filename,
                         DataFirstPasser *data, SecondPasser *second) {
    output << "H: " << filename << std::endl;
    output << "H: " << data->getFinalAddress() << std::endl;
}

void outputAssembledProgram(std::ofstream &output, DataFirstPasser *data,
                            SecondPasser *second) {
    outputAssembledInstructions(output, second);
    outputAssembledData(output, data);
    output.flush();
    output.close();
}

void printAllErrors(DataFirstPasser *data,
                    CodeFirstPasser *first, SecondPasser *second) {
    printErrors(data->getErrors());
    printErrors(first->getErrors());
    printErrors(second->getErrors());
}

void outputAssembledData(std::ofstream &output, DataFirstPasser *data) {
    for (auto &dataLine : data->getDataLines())
        if (dataLine.hasOperation())
            output << " " << dataLine.getValue();
}

void outputAssembledInstructions(std::ofstream &output, SecondPasser *second) {
    int lineCount = second->getLineCount();
    for (auto pl : second->getProcessedLines())
        output << pl << ((--lineCount > 0)?" ":"");
}

bool hasErrors(SecondPasser *second) {
    return second->getErrorCount() > 0;
}

bool hasErrors(CodeFirstPasser *passer) {
    return passer->getErrorCount() > 0;
}

bool hasErrors(DataFirstPasser *passer) {
    return passer->getErrorCount() > 0;
}

void printErrors(std::vector<ParsingError> errors) {
    for (auto &error : errors)
        std::cout << error.what() << std::endl;
}

std::string readFile(std::string filename) {
    std::ifstream t(filename);
    return std::string ((std::istreambuf_iterator<char>(t)),
                        std::istreambuf_iterator<char>());
}
