cmake_minimum_required(VERSION 3.12)
project(ats-yaml)

set(CMAKE_CXX_STANDARD 14)
link_directories(/usr/local/lib)

add_executable(untitled main.cpp YTSConfig.h YTSConfig.cpp)
target_include_directories(untitled PUBLIC /usr/local/include/yaml-cpp)
target_link_libraries(untitled yaml-cpp)