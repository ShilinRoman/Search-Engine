cmake_minimum_required (VERSION 3.8)

project("search-engine")

set(Src
        converterJSON.cpp
        searchServer.cpp
        invertedIndex.cpp
        main.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
add_executable(${PROJECT_NAME} ${Src})

target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)
target_include_directories(${PROJECT_NAME} PUBLIC ${MY_INCLUDE_DIR})