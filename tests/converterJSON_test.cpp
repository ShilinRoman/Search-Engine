#include "converterJSON.h"
#include "gtest/gtest.h"

TEST(converterJSON, readConfig) {
    std::ifstream file ("json_files\\config.json");
    ASSERT_TRUE(file.is_open()) << "File \"requests.json\" not open";
    std::cout << "The test is passed" << std::endl;
}

TEST(converterJSON, readRequests) {
    std::ifstream file ("json_files\\requests.json");
    ASSERT_TRUE(file.is_open()) << "File \"config.json\" not open";
    std::cout << "The test is passed" << std::endl;
}

TEST(converterJSON, getResponsesLimit) {
    ConverterJSON converter;
    try
    {
        int expected = 5;
        int responses = converter.getResponsesLimit();
        ASSERT_EQ(expected, responses);
        std::cout << "The test is passed" << std::endl;
    }
    catch (const char* message) {
        std::cerr << message << std::endl;
    }
}

TEST(converterJSON, getRequests) {
    ConverterJSON converter;
    try
    {
        size_t expectedRequests = 1;
        size_t numberRequests = converter.getRequests().size();
        ASSERT_EQ(expectedRequests, numberRequests);
        std::cout << "The test is passed" << std::endl;
    }
    catch (const char* message) {
        std::cerr << message << std::endl;
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
            auto numberFiles = dict["files"].size();
            ASSERT_EQ(expectedFiles, numberFiles);
        }
        else
        {
            std::cerr << "Error: no files" << std::endl;
        }
    }
}

TEST(converterJSON, putAnswers) {
    std::ifstream answers ("json_files\\answers.json");
    ASSERT_TRUE(answers) << "File \"answers.json\" not open";
    std::cout << "The test is passed" << std::endl;
}
