#ifndef SEARCH_ENGINE_INVERTEDINDEX_H
#define SEARCH_ENGINE_INVERTEDINDEX_H

#include <map>
#include <string>
#include <vector>

struct Entry
{
    size_t doc_id, count;

    bool operator==(const Entry &other) const
    {
        return(doc_id == other.doc_id && count == other.count);
    }
};

class InvertedIndex {
public:
    InvertedIndex() = default;
    void updateDocumentBase(std::vector <std::string> input_docs);
    std::vector <Entry> getWordCount(const std::string& word);
    std::map <std::string, std::vector <Entry>> getDictionary();

private:
    std::vector <std::string> docs;
    std::map <std::string, std::vector <Entry>> freqDictionary;
};

#endif //SEARCH_ENGINE_INVERTEDINDEX_H
