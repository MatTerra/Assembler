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

void outputHeader(std::ofstream &output, std::string headerContent);

int assembleFile(std::string filename);

std::string getBaseName(std::string filename);

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "Expected at least 1 filename as argument to executable!";
        return 1;
    }
    std::vector<std::string> files;
    for (int i = 1; i < argc; i++) {
        auto filename = std::string(argv[i]);
        auto extension = filename.substr(filename.find_last_of('.'));
        if (extension != ".asm"){
            std::cout << "Expected an .asm file!";
            return 1;
        }
        files.insert(files.end(), filename);
    }
    auto foundErrors = 0;

    for (auto filename : files) {
        std::cout << "assembling " << filename << std::endl;
        foundErrors += assembleFile(filename);
    }

    return foundErrors;
}

int assembleFile(std::string filename) {
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
    std::cout << "Generating output in: " << filename.substr(0, filename.find_last_of('.'))+".obj" << std::endl;
    output.open(filename.substr(0, filename.find_last_of('.'))+".obj") ;
    outputProgramHeader(output, getBaseName(filename), data, second);
    outputAssembledProgram(output, data, second);
    output.close();

    return 0;
}

std::string readFile(std::string filename) {
    std::ifstream t(filename);
    return std::string ((std::istreambuf_iterator<char>(t)),
                        std::istreambuf_iterator<char>());
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

bool hasErrors(SecondPasser *second) {
    return second->getErrorCount() > 0;
}

bool hasErrors(CodeFirstPasser *passer) {
    return passer->getErrorCount() > 0;
}

bool hasErrors(DataFirstPasser *passer) {
    return passer->getErrorCount() > 0;
}

void printAllErrors(DataFirstPasser *data,
                    CodeFirstPasser *first, SecondPasser *second) {
    printErrors(data->getErrors());
    printErrors(first->getErrors());
    printErrors(second->getErrors());
}

void printErrors(std::vector<ParsingError> errors) {
    for (auto &error : errors)
        std::cout << error.what() << std::endl;
}

void outputProgramHeader(std::ofstream &output, std::string filename,
                         DataFirstPasser *data, SecondPasser *second) {
    outputHeader(output, filename);
    outputHeader(output, std::to_string(data->getFinalAddress()));
    outputHeader(output, second->getRelocationBitmap().append(data->getRelocationBitmap()));
    auto useTable = second->getUseTable();
    if (useTable->getUsedSymbols().size() > 0){
        for (auto symbol : useTable->getUsedSymbols()) {
            std::stringstream usesString;
            usesString << "U " << symbol;
            auto uses = useTable->getSymbolUse(symbol);
            for (auto use: uses){
                usesString << " " << use;
            }
            outputHeader(output, usesString.str());
        }
    }
}

void outputHeader(std::ofstream &output, std::string headerContent){
    output << "H: " << headerContent << std::endl;
    output.flush();
}

std::string getBaseName(std::string filename) {
    unsigned int baseNameStart = filename.find_last_of('/') + 1;
    unsigned int baseNameLength = filename.find_last_of('.') - baseNameStart;
    std::string baseFileName = filename.substr(baseNameStart, baseNameLength);
    return baseFileName;
}

void outputAssembledProgram(std::ofstream &output, DataFirstPasser *data,
                            SecondPasser *second) {
    output << "T: ";
    outputAssembledInstructions(output, second);
    outputAssembledData(output, data);
    output << std::endl;
    output.flush();
}

void outputAssembledInstructions(std::ofstream &output, SecondPasser *second) {
    int lineCount = second->getLineCount();
    for (auto pl : second->getProcessedLines())
        output << pl << ((--lineCount > 0)?" ":"");
}

void outputAssembledData(std::ofstream &output, DataFirstPasser *data) {
    for (auto &dataLine : data->getDataLines())
        if (dataLine.hasOperation())
            output << " " << dataLine.getValue();
}
