#ifndef SEARCH_ENGINE_SEARCHSERVER_H
#define SEARCH_ENGINE_SEARCHSERVER_H

#include <vector>

#include "invertedIndex.h"

struct RelativeIndex
{
    size_t doc_id;
    float rank;

    bool operator==(const RelativeIndex &other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

class SearchServer {
public:
    SearchServer(InvertedIndex& idx): index(idx) {}
    std::vector <std::vector <RelativeIndex>> search (const std::vector <std::string>& queriesInput);

private:
    InvertedIndex index;
};
#endif //SEARCH_ENGINE_SEARCHSERVER_H
