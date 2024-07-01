#ifndef SEARCH_ENGINE_CONVERTERJSON_H
#define SEARCH_ENGINE_CONVERTERJSON_H

#include <fstream>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

class ConverterException : public std::exception {
public:
    explicit ConverterException (const std::string& newMessage) : message(newMessage) {}
    const char* what() const noexcept override;

private:
    std::string message;
};

class ConverterJSON {
public:
    ConverterJSON() = default;
    std::vector <std::string> getTextDocument ();
    int getResponsesLimit ();
    std::vector <std::string> getRequests ();
    void putAnswers (std::vector <std::vector <std::pair <size_t, float>>> answers);

private:
    std::string version = "0.1";
};
#endif //SEARCH_ENGINE_CONVERTERJSON_H
