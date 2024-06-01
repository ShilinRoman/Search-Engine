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
                relevanceData.emplace_back(doc_id, rank);
            }
            answers.push_back(relevanceData);
        }

        converter.putAnswers(answers);
    }
    catch (const std::exception& x) {
        std::cerr << "Error: " << x.what() << std::endl;
    }
}

int main()
{
    launchingSearchEngine();
    ConverterJSON converter;
    try
    {
        int limit = converter.getResponsesLimit();
        std::cout << "Limit: " << limit << std::endl;
    }
    catch (const std::exception& x) {
        std::cerr << "Error: " << x.what() << std::endl;
    }
    return 0;
}
