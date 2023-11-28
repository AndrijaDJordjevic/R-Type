cmake_minimum_required(VERSION 3.13)
project(LibLoader)

set(CMAKE_CXX_STANDARD 20)

add_library(LibLoader STATIC
        Headers/Lib.hpp Sources/Lib.cpp
        Headers/Exceptions/FileNotFound.hpp Sources/Exceptions/FileNotFound.cpp
        Headers/Exceptions/DlError.hpp Sources/Exceptions/DlError.cpp
        Headers/Exceptions/NullReference.hpp Sources/Exceptions/NullReference.cpp
)

target_include_directories(LibLoader PUBLIC Headers)
