#include <map>
#include <set>
#include <string>
#include <sstream>

#include "searchServer.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queriesInput)
{
    std::vector <std::vector <RelativeIndex>> answers;
    auto dictionary = index.getDictionary();

    if (!queriesInput.empty())
    {
        for (auto& request : queriesInput)
        {
            std::set <std::string> uniqueWords;
            std::stringstream ss(request.c_str());
            std::string bufferWord;
            while (ss >> bufferWord)
            {
                uniqueWords.insert(bufferWord);
            }

            std::map <size_t, std::string> sortedFrequencyWords; // <quantity, word>
            for (auto& word : uniqueWords)
            {
                auto it = dictionary.find(word);
                if (it != dictionary.end())
                {
                    size_t min = it->second.begin()->count;
                    for (auto& value : it->second)
                    {
                        min = std::min(value.count, min);
                    }
                    sortedFrequencyWords.insert({min, word});
                }
            }

            if (!sortedFrequencyWords.empty())
            {
                std::multimap <size_t, size_t> absoluteRelevance; // <absolute relevance, doc_id>
                bool isResult = false;
                auto itFirstWord = sortedFrequencyWords.begin();
                auto it = dictionary.find(itFirstWord->second);

                if (it != dictionary.end())
                {
                    for (auto& value : it->second)
                    {
                        size_t  counter = sortedFrequencyWords.size() - 1;
                        auto itNext = dictionary.find((++itFirstWord)->second);
                        if (itNext != dictionary.end())
                        {
                            for (auto& nextValue : itNext->second)
                            {
                                if (value.doc_id == nextValue.doc_id)
                                {
                                    --counter;
                                }
                            }
                        }

                        if (counter == 0)
                        {
                            isResult = true;
                        }

                        if (isResult)
                        {
                            size_t absCount = 0;
                            for (auto& word : uniqueWords)
                            {
                                auto itWord = dictionary.find(word);
                                if (itWord != dictionary.end())
                                {
                                    for (auto& dictValue : itWord->second)
                                    {
                                        if (value.doc_id == dictValue.doc_id)
                                        {
                                            absCount += dictValue.count;
                                        }
                                    }
                                }
                            }
                            absoluteRelevance.insert({absCount, value.doc_id});
                        }
                    }
                }

                if (!absoluteRelevance.empty())
                {
                    std::vector <RelativeIndex> relativeRelevance;
                    auto maxAbsCount = absoluteRelevance.rbegin();

                    RelativeIndex relativeIndex;
                    for (auto& document : absoluteRelevance)
                    {
                        relativeIndex.doc_id = document.second;
                        relativeIndex.rank = document.first / static_cast <float> (maxAbsCount->first);
                        relativeRelevance.push_back(relativeIndex);
                    }

                    for (size_t i = 0; i < relativeRelevance.size()-1; ++i)
                    {
                        size_t max = i;
                        for (size_t j = i+1; j < relativeRelevance.size(); ++j)
                        {
                            if (relativeRelevance[j].rank > relativeRelevance[max].rank) max = j;
                        }
                        if (max != i)
                        {
                            auto temp = relativeRelevance[max];
                            relativeRelevance[max] = relativeRelevance[i];
                            relativeRelevance[i] = temp;
                        }
                    }
                    answers.push_back(relativeRelevance);
                }
            }
            else
            {
                answers.push_back({});
            }
        }
    }
    return answers;
}