#include <iostream>
#include <vector>

#include "converterJSON.h"
#include "invertedIndex.h"
#include "searchServer.h"

void launchingSearchEngine ()
{
    ConverterJSON converter;
    InvertedIndex idx;
    try {
        idx.updateDocumentBase(converter.getTextDocument());
        SearchServer server(idx);

        std::vector <std::vector <std::pair <size_t, float>>> answers;

        for (auto& element : server.search(converter.getRequests()))
        {
            std::vector <std::pair <size_t, float>> relevanceData;
            for (auto& [doc_id, rank] : element)
            {
                relevanceData.push_back({doc_id, rank});
            }
            answers.push_back(relevanceData);
        }

        converter.putAnswers(answers);
    }
    catch (const char* message) {
        std::cerr << message << std::endl;
    }
}

int main()
{
    launchingSearchEngine();
    return 0;
}
