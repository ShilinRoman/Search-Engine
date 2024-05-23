#include "converterJSON.h"
#include "gtest/gtest.h"

class ConfigTest: public ::testing::Test
{
public:
    ConverterJSON converter;
};

TEST_F(ConfigTest, readConfig)
{
    ASSERT_ANY_THROW(converter.getTextDocument());
}

TEST(converterJSON, readConfig) {

}

TEST(converterJSON, readRequests) {

}

TEST(converterJSON, getResponsesLimit) {

}

TEST(converterJSON, getRequests) {

}

TEST(converterJSON, getFiles) {

}

TEST(converterJSON, putAnswers) {

}
