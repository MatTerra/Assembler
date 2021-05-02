//
// Created by mateusberardo on 08/03/2021.
//

#include <string>
#include <utility>
#include <iostream>
#include <algorithm>
#include "sectionextractor.h"
#include "stringutils.h"

SectionExtractor::SectionExtractor(std::string content, bool isModule)
    :fileContent(std::move(content)), isModule(isModule) {
    lowerCaseString(fileContent);
    auto start = findSectionKeywordFromOffset(0);

    removeEnd();

    while (start != std::string::npos) {
        proccessSection(start);
        start = findSectionKeywordFromOffset(start+7);
    }

}

void SectionExtractor::removeEnd() {
    if (isModule) {
        int endIndex = fileContent.find_last_of("end");
        fileContent.erase(endIndex - 2, 3);
    }
}

void SectionExtractor::proccessSection(unsigned long start) {
    auto sectionType = getSectionType(start);
    if (sectionType == UNKNOWN)
        std::cout << "unknown type: " << extractSectionTypeName(start);
    if (sectionType == DATA)
        extractDataSection(start);
    else if (sectionType == TEXT)
        extractTextSection(start);
}

void SectionExtractor::extractTextSection(unsigned long start) {
    textSection = getSection(start);
    textLineOffset = getSectionLineOffset(start);
}

void SectionExtractor::extractDataSection(int start) {
    dataLineOffset = getSectionLineOffset(start);
    dataSection = getSection(start);
}

long SectionExtractor::getSectionLineOffset(int start) {
    return std::count(fileContent.begin(),
                      (fileContent.begin() + (fileContent.find('\n', start) + 1)),
                      '\n') + 1;
}

std::string SectionExtractor::getSection(size_t start=0) const {
    auto sectionHeaderStart = findSectionKeywordFromOffset(start);
    auto sectionStart = fileContent.find_first_of('\n', sectionHeaderStart) + 1;
    auto sectionEnd = findSectionKeywordFromOffset(sectionStart);
    auto sectionContent = fileContent.substr(sectionStart, sectionEnd - sectionStart);
    return sectionContent;
}

std::string SectionExtractor::getFileContent() {
    return fileContent;
}

std::string SectionExtractor::getDataSection() {
    return dataSection;
}

SectionTypes SectionExtractor::getSectionType(size_t start) {
    auto sectionType = extractSectionTypeName(start);
    lowerCaseString(sectionType);

    if (sectionType == "data")
        return SectionTypes::DATA;
    else if (sectionType == "text")
        return SectionTypes::TEXT;
    return SectionTypes::UNKNOWN;
}

std::string SectionExtractor::extractSectionTypeName(
        unsigned long sectionHeaderStart) const {
    auto sectionTypeStart = fileContent.find_first_not_of(whitespaces, sectionHeaderStart + 7);
    auto sectionTypeEnd = fileContent.find_first_of(whitespaces, sectionTypeStart);
    auto sectionType = fileContent.substr(sectionTypeStart, sectionTypeEnd - sectionTypeStart);
    return sectionType;
}

unsigned long SectionExtractor::findSectionKeywordFromOffset(size_t offset) const {
    return fileContent.find("section", offset);
}

int SectionExtractor::getDataLineOffset() {
    return dataLineOffset;
}

std::string SectionExtractor::getTextSection() {
    return textSection;
}

int SectionExtractor::getTextLineOffset() {
    return textLineOffset;
}
