cmake_minimum_required(VERSION 3.4)
project(word_seg_max_match)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp  CreatDic.h )

add_executable(word_seg_max_match ${SOURCE_FILES})