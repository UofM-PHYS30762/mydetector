cmake_minimum_required(VERSION 4.2)
project(gdetector)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(gdetector)
target_sources(gdetector
        PRIVATE
        src/gdetector.cc

        PUBLIC
        FILE_SET HEADERS
        FILES
        include/gdetector/gdetector.h
)
target_include_directories(gdetector
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_subdirectory(tests)
