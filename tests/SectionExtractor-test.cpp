//
// Created by mateusberardo on 08/03/2021.
//

#include "gtest/gtest.h"
#include <sectionextractor.h>

TEST(SectionExtractor, may_instantiate){
    auto se = new SectionExtractor("section data\nlabel: const 8\nsection text\nstop");
    ASSERT_NE(nullptr, se);
}

TEST(SectionExtractor, may_get_raw_file){
    auto line = "section data\nlabel: const 8\nsection text\nstop";
    auto se = new SectionExtractor(line);
    ASSERT_EQ(line, se->getFileContent());
}

TEST(SectionExtractor, may_get_data_content){
    auto line = "section data\nlabel: const 8\nsection text\nstop";
    auto dataContent = "label: const 8\n";
    auto se = new SectionExtractor(line);
    ASSERT_EQ(dataContent, se->getDataSection());
}

TEST(SectionExtractor, may_get_data_content_case_insensitive){
    auto line = "section dAtA\nlabel: const 8\nsection text\nstop";
    auto dataContent = "label: const 8\n";
    auto se = new SectionExtractor(line);
    ASSERT_EQ(dataContent, se->getDataSection());
}

TEST(SectionExtractor, may_get_data_content_after){
    auto line = "section text\nstop\nsection data\nlabel: const 8";
    auto dataContent = "label: const 8";
    auto se = new SectionExtractor(line);
    ASSERT_EQ(dataContent, se->getDataSection());
}

TEST(SectionExtractor, may_get_data_starting_line){
    auto line = "section data\nlabel: const 8\nsection text\nstop\n";
    auto se = new SectionExtractor(line);
    ASSERT_EQ(2, se->getDataLineOffset());
}

TEST(SectionExtractor, may_get_data_line_offset_after){
    auto line = "section text\nstop\nsection data\nlabel: const 8";
    auto se = new SectionExtractor(line);
    ASSERT_EQ(4, se->getDataLineOffset());
}

TEST(SectionExtractor, may_get_data_with_weird_spaces){
    auto line = "\n\t  section \t data\nlabel: const 8\nsection text\nstop";
    auto dataContent = "label: const 8\n";
    auto se = new SectionExtractor(line);
    ASSERT_EQ(dataContent, se->getDataSection());
}

TEST(SectionExtractor, may_get_data_with_blank_spaces_before){
    auto line = "\n\n\t section data\nlabel: const 8\nsection text\nstop";
    auto dataContent = "label: const 8\n";
    auto se = new SectionExtractor(line);
    ASSERT_EQ(dataContent, se->getDataSection());
}

TEST(SectionExtractor, data_should_be_blank_if_not_defined){
    auto line = "section text\nstop";
    auto dataContent = "";
    auto se = new SectionExtractor(line);
    ASSERT_EQ(dataContent, se->getDataSection());
}

TEST(SectionExtractor, shouldnt_crash_if_unknown_section){
    auto line = "section resources\nstop";
    auto dataContent = "";
    auto se = new SectionExtractor(line);
    ASSERT_EQ(dataContent, se->getDataSection());
}

TEST(SectionExtractor, may_get_text_content){
    auto line = "section data\nlabel: const 8\nsection text\nstop";
    auto dataContent = "stop";
    auto se = new SectionExtractor(line);
    ASSERT_EQ(dataContent, se->getTextSection());
}

TEST(SectionExtractor, may_get_text_content_case_insensitive){
    auto line = "section data\nlabel: const 8\nsection tEXt\nstop";
    auto dataContent = "stop";
    auto se = new SectionExtractor(line);
    ASSERT_EQ(dataContent, se->getTextSection());
}

TEST(SectionExtractor, may_get_text_content_first){
    auto line = "section text\nstop\nsection data\nlabel: const 8";
    auto dataContent = "stop\n";
    auto se = new SectionExtractor(line);
    ASSERT_EQ(dataContent, se->getTextSection());
}

TEST(SectionExtractor, may_get_text_starting_line){
    auto line = "section data\nlabel: const 8\nsection text\nstop\n";
    auto se = new SectionExtractor(line);
    ASSERT_EQ(4, se->getTextLineOffset());
}

TEST(SectionExtractor, may_get_text_line_offset_first){
    auto line = "section text\nstop\nsection data\nlabel: const 8";
    auto se = new SectionExtractor(line);
    ASSERT_EQ(2, se->getTextLineOffset());
}