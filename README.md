# Search-Engine

Description of the project:  Local search engine

The stack of technologies used:  C++, Nlohmann_json, GoogleTest

Instruction manual: To download the program archive, click on the Code button.
Unzip the archive data to a new folder. You can use MinGW64 for compilation.
To compile the program, go to the project folder on the command line, then select the src folder and run the command:

g++ main.cpp converterJSON.cpp invertedIndex.cpp searchServer.cpp -o search-engine .exe

Then run the program with the command:

search-engine.exe

The search engine is a console application
that performs a search and has the ability to configure through JSON format
files. The solutions applied in it can later be integrated into
a web-based search engine.

The principles of the search engine:
- In the "config.json" configuration file, before launching the application, the names
of the files in the "files" field are set, which the engine will search for.
- The search engine independently crawls all files and
indexes them so that it can then find the most
relevant documents for any search query.
- The user makes a request through the JSON file "requests.json", then the request is transformed into a list of words.
- The index searches for those documents on which all these words occur.
- The search results are ranked, sorted and given to the user,
the maximum number of possible documents in the response is set in
the configuration file "config.json" in the "max_responses" field.
- At the end, the program generates the file "answers.json", which records
the search results.
