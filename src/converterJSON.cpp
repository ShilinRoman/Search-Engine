#include <iostream>
#include <exception>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "nlohmann/json.hpp"
#include "converterJSON.h"

using json = nlohmann::json;

std::vector<std::string> ConverterJSON::getTextDocument() {
    std::vector <std::string> textDocuments;
    std::ifstream fileConfig ("json_files\\config.json");

    if (fileConfig.is_open())
    {
        json dict;
        fileConfig >> dict;
        if (dict.contains("config"))
        {
            bool compareVersions = (dict["config"]["version"] == version);
            if (compareVersions)
            {
                std::cout << dict["config"]["name"] << " v." << dict["config"]["version"] << std::endl;

                if (!dict["files"].empty())
                {
                    for (const auto& element : dict["files"])
                    {
                        std::string currentText;
                        std::ifstream files (element);

                        if (files.is_open())
                        {
                            currentText.assign(std::istreambuf_iterator<char>(files),std::istreambuf_iterator<char>());
                            textDocuments.push_back(currentText);
                        }
                        else
                        {
                            std::cerr << "File " << element << " does not exist" << std::endl;
                        }
                        files.close();
                    }
                }
                else
                {
                    throw ConverterException ("files are missing");
                }
            }
            else
            {
                throw ConverterException ("\"config.json\" has incorrect file version");
            }
        }
        else
        {
            throw ConverterException ("\"config\" file is empty");
        }
    }
    else
    {
        throw ConverterException ("\"config\" file is missing");
    }
    fileConfig.close();
    return textDocuments;
}

int ConverterJSON::getResponsesLimit() {
    std::ifstream file ("json_files\\config.json");

    if (!file.is_open())
    {
        throw ConverterException ("file \"config.json\" not open");
    }

    json dict;
    file >> dict;

    int defaultResponses = 5;
    int currentResponses = dict["config"]["max_responses"];
    int responses = (dict["config"]["max_responses"].empty()) ? defaultResponses : currentResponses;
    file.close();
    return responses;
}

std::vector<std::string> ConverterJSON::getRequests() {
    std::vector<std::string> requests;
    std::ifstream file("json_files\\requests.json");

    if (!file.is_open())
    {
        throw ConverterException ("file \"requests.json\" not open");
    }

    json dict;
    file >> dict;

    for (const auto& element : dict["requests"])
    {
        requests.push_back(element);
    }
    file.close();
    return requests;
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair <size_t, float>>> answers) {
    nlohmann::ordered_json dict;
    int i = 0;
    std::ofstream  file ("json_files\\answers.json", std::ios::trunc);

    if (file.is_open()) {
        for (auto &request: answers) {
            std::stringstream ss;
            ss << "request" << std::setfill('0') << std::setw(3) << i;

            if (!request.empty()) {
                dict["answers"][ss.str()]["result"] = true;
                int responsesLimit = getResponsesLimit();

                for (auto &[doc_id, rank]: request) {
                    if (responsesLimit == 0) break;
                    if (request.size() == 1) {
                        dict["answers"][ss.str()]["docid"] = doc_id;
                        dict["answers"][ss.str()]["rank"] = rank;
                    }
                    if (request.size() > 1) {
                        dict["answers"][ss.str()]["relevance"].push_back({{"docid", doc_id},
                                                                          {"rank",  rank}});
                    }
                    --responsesLimit;
                }
            } else {
                dict["answers"][ss.str()]["result"] = false;
            }
            ++i;
        }
        file << dict.dump(4);
    }
}

const char* ConverterException::what() const noexcept {
    return message.c_str();
}
