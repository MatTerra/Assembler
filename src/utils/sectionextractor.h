//
// Created by mateusberardo on 08/03/2021.
//

#ifndef MONTADOR_SECTIONEXTRACTOR_H
#define MONTADOR_SECTIONEXTRACTOR_H

enum SectionTypes{
    NOSECTION=-1,
    DATA=1,
    TEXT=2,
    UNKNOWN=3
};


class SectionExtractor {

public:
    SectionExtractor(std::string content);

    std::string getFileContent();

    std::string getDataSection();


    int getDataLineOffset();

    std::string getTextSection();

    int getTextLineOffset();

private:
    std::string fileContent;
    std::string dataSection;

    std::string getSection(size_t start) const;

    SectionTypes getSectionType(size_t start);

    unsigned long findSectionKeywordFromOffset(size_t offset) const;

    std::string extractSectionTypeName(unsigned long sectionHeaderStart) const;

    int dataLineOffset;

    long getSectionLineOffset(int start);

    void extractDataSection(int start);

    std::string textSection;
    int textLineOffset;

    void extractTextSection(unsigned long start);

    void proccessSection(unsigned long start);
};


#endif //MONTADOR_SECTIONEXTRACTOR_H
