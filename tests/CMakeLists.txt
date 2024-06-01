cmake_minimum_required (VERSION 3.8)

project("search-engine-test")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(SrcFiles
        ${MY_SRC_DIR}/invertedIndex.cpp
        ${MY_SRC_DIR}/searchServer.cpp
        ${MY_SRC_DIR}/converterJSON.cpp
)

set(TestsFiles
        invertedIndex_test.cpp
        searchServer_test.cpp
        converterJSON_test.cpp
)

add_executable(${PROJECT_NAME} ${TestsFiles} ${SrcFiles})
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json GTest::gtest_main)
include(GoogleTest)
target_include_directories(${PROJECT_NAME} PUBLIC ${MY_INCLUDE_DIR})
gtest_discover_tests(${PROJECT_NAME})
