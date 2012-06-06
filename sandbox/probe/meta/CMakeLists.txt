cmake_minimum_required(VERSION 2.6)
project(meta-0.1)
include_directories(../../../faslib2)
ADD_DEFINITIONS(-DFASLIB_TYPE_LIST_CHECK)
add_executable(meta meta.cpp)

