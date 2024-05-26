#include "converterJSON.h"
#include "invertedIndex.h"
#include "gtest/gtest.h"

TEST(converterJSON, readConfig) {
    ConverterJSON converter;
    json dict;


}

TEST(converterJSON, readRequests) {

}

TEST(converterJSON, getResponsesLimit) {
    ConverterJSON converter;
    int expected = 5;
    int responses = converter.getResponsesLimit();
    ASSERT_EQ(expected, responses);
}

TEST(converterJSON, getRequests) {
    ConverterJSON converter;
    size_t expectedRequests = 1;
    size_t numberRequests = converter.getRequests().size();
    ASSERT_EQ(expectedRequests, numberRequests);
}

TEST(converterJSON, getFiles) {
    std::ifstream file ("json_files\\config.json");
    json dict;
    file >> dict;

    if (!dict["files"].empty())
    {
        auto expectedFiles = 26;
        auto numberFiles = dict["files"].size();
        ASSERT_EQ(expectedFiles, numberFiles);
    }
    else
    {
        std::cerr << "Error: no files" << std::endl;
    }
}

TEST(converterJSON, putAnswers) {
    
}
