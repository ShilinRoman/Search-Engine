#include "invertedIndex.h"
#include "gtest/gtest.h"

TEST(InvertedIndex, updateDocumentBase) {
    const std::vector<std::string>& textDocument = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuccino"
    };
    InvertedIndex inx;
    inx.updateDocumentBase(textDocument);

    std::map <std::string, std::vector <Entry>> expected = {
            {
                "americano", {{3, 1}}
            },
            {
                "cappuccino", {{3, 1}}
            },
            {
                "milk", {{0, 4}, {1, 1}, {2, 5}}
            },
            {
                "water", {{0, 3}, {1, 2}, {2, 5}}
            }
    };
    ASSERT_EQ(inx.getDictionary(), expected);
}

TEST(InvertedIndex, getWordCount) {
    const std::vector<std::string>& textDocument = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuccino"
    };
    InvertedIndex inx;
    inx.updateDocumentBase(textDocument);
    std::string word = "milk";
    std::vector <Entry> expected = {
            {0, 4}, {1, 1}, {2, 5}
    };
    ASSERT_EQ(inx.getWordCount(word), expected);
}