cmake_minimum_required(VERSION 3.13)
project(ECS)

set(SOURCES
    Sources/Registry.cpp
)

set(HEADERS
    Headers/SparseArray.hpp
    Headers/Registry.hpp
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

add_library(ECSlib ${SOURCES} ${HEADERS})
target_include_directories(ECSlib PUBLIC Headers)
