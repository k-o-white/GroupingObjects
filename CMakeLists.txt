cmake_minimum_required(VERSION 3.23)
project(GroupingObjects)

set(CMAKE_CXX_STANDARD 20)

set(MY_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")