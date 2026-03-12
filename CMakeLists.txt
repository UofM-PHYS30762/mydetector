cmake_minimum_required(VERSION 4.2)
project(mydetector)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(mydetector)
target_sources(mydetector
        PRIVATE
        src/gdetector.cc

        PUBLIC
        FILE_SET HEADERS
        FILES
        include/gdetector/gdetector.h
)
target_include_directories(mydetector
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_subdirectory(tests)
