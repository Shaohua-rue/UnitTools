cmake_minimum_required(VERSION 3.0)
project(logger) #锁定项目的工作目录

#设置全局的c++标准
set (CMAKE_CXX_STANDARD 11) 
set (CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(
    include
)

file(GLOB SRC_FILES
    src/*.cc
)
add_executable(logger_test ${SRC_FILES})
