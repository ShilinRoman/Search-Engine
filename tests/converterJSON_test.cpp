#include "converterJSON.h"
#include "gtest/gtest.h"

TEST(converterJSON, readConfig) {
    std::ifstream config ("json_files\\config.json");
    ASSERT_TRUE(config.is_open()) << "File \"config.json\" not open";
    std::cout << "The test is passed" << std::endl;
}

TEST(converterJSON, readRequests) {
    std::ifstream requests ("json_files\\requests.json");
    ASSERT_TRUE(requests.is_open()) << "File \"requests.json\" not open";
    std::cout << "The test is passed" << std::endl;
}

TEST(converterJSON, getResponsesLimit) {
    ConverterJSON converter;
    try
    {
        int expectedResponses = 5;
        int actualResponses = converter.getResponsesLimit();
        ASSERT_EQ(expectedResponses, actualResponses);
        std::cout << "The test is passed" << std::endl;
    }
    catch (const std::exception& x) {
        std::cerr << "Error: " << x.what() << std::endl;
    }
}

TEST(converterJSON, getRequests) {
    ConverterJSON converter;
    try
    {
        size_t expectedRequests = 1;
        size_t actualRequests = converter.getRequests().size();
        ASSERT_EQ(expectedRequests, actualRequests);
        std::cout << "The test is passed" << std::endl;
    }
    catch (const std::exception& x) {
        std::cerr << "Error: " << x.what() << std::endl;
    }
}

TEST(converterJSON, getFiles) {
    std::ifstream config ("json_files\\config.json");
    ASSERT_TRUE(config.is_open()) << "File \"config.json\" not open";

    if (config.is_open())
    {
        json dict;
        config >> dict;

        if (!dict["files"].empty())
        {
            auto expectedFiles = 26;
            auto actualFiles = dict["files"].size();
            ASSERT_EQ(expectedFiles, actualFiles);
        }
        else
        {
            std::cerr << "Error: no files" << std::endl;
        }
    }
}

TEST(converterJSON, putAnswers) {
    std::ifstream answers ("json_files\\answers.json");
    ASSERT_TRUE(answers.is_open()) << "File \"answers.json\" not open";
    std::cout << "The test is passed" << std::endl;
}
