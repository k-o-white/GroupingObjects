cmake_minimum_required(VERSION 3.23)

add_executable(GroupingObjects
        main.cpp
        Object.cpp
        ReadWrite.cpp
        GroupingOptions.cpp
        ${MY_INCLUDE_PATH}/Object.h
        ${MY_INCLUDE_PATH}/GroupingOptions.h
        ${MY_INCLUDE_PATH}/ReadWrite.h )

target_include_directories(GroupingObjects PUBLIC ${MY_INCLUDE_PATH})