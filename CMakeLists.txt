# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.0)
set (CMAKE_CXX_STANDARD 20)

# Project's name

project(nikrequest)
# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
# This line will export your dependency's symbols and make them available to your project on Windows. Without this your code will compile but it won't run on Windows!
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}")

add_library(nikrequest STATIC)

target_sources(nikrequest PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/HttpRequest.cpp
)

target_include_directories(nikrequest PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# We can now add their CMakeList as a child to ours.
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/curlpp/)
# You may want to add library's include directories since your code might use their header files. If libdependency is exporting its symbols properly you shouldn't have to do this though.
target_include_directories(curlpp PUBLIC ${PROJECT_SOURCE_DIR}/lib/curlpp/include)

target_link_libraries(nikrequest PUBLIC curlpp)