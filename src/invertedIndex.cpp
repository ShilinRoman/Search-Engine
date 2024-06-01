#include "invertedIndex.h"

void InvertedIndex::updateDocumentBase(std::vector<std::string> inputDocs)
{
    if (!docs.empty())
        docs.clear();

    docs = std::move(inputDocs);
    std::string word;
    std::mutex mtx;
    std::vector <std::thread> threads;
    threads.reserve(docs.size());

    for (auto& element : docs)
    {
        std::stringstream ss (element);
        while (ss >> word)
        {
            for (size_t i = 0; i < docs.size(); ++i)
            {
                threads.emplace_back(std::thread([=, this, &mtx](){
                    std::lock_guard <std::mutex> lockMtx (mtx);
                    freqDictionary.insert ({word, {getWordCount(word)}});
                }));
            }

            for (auto& thread : threads)
            {
                if (thread.joinable())
                {
                    thread.join();
                }
            }
        }
    }
}

std::vector<Entry> InvertedIndex::getWordCount(const std::string& word)
{
    std::vector <Entry> wordsCount;
    Entry entry;

    for (entry.doc_id = 0; entry.doc_id < docs.size(); ++entry.doc_id)
    {
        std::stringstream ss (docs[entry.doc_id]);
        std::string tempWord;
        entry.count = 0;

        while (ss >> tempWord)
        {
            if (word == tempWord){
                ++entry.count;
            }
        }
        if (entry.count != 0)
        {
            wordsCount.push_back(entry);
        }
    }
    return wordsCount;
}

std::map<std::string, std::vector<Entry>> InvertedIndex::getDictionary() {
    return freqDictionary;
}