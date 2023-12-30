cmake_minimum_required(VERSION 3.22)
project(aoc2023)

set(CXX_STANDARD 17)

find_package(GTest REQUIRED)
find_package(spdlog REQUIRED)
find_package(absl REQUIRED)

enable_testing()

add_executable(aoc2023 1.cpp 2.cpp 3.cpp 4.cpp 5.cpp)
target_link_libraries(aoc2023 PRIVATE spdlog::spdlog GTest::gtest_main gmock absl::strings)

include(GoogleTest)
gtest_discover_tests(aoc2023)