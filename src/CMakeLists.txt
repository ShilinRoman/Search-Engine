cmake_minimum_required (VERSION 3.8)

set(Src
        converterJSON.cpp
        searchServer.cpp
        invertedIndex.cpp
        main.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
add_executable(Search-Engine ${Src})

target_link_libraries(Search-Engine nlohmann_json::nlohmann_json)
target_include_directories(Search-Engine PUBLIC ${MY_INCLUDE_DIR})