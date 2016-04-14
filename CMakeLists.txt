cmake_minimum_required(VERSION 3.4)
project(AwesomeScheduler)

include_directories(header)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(DISPTACHER_SOURCE_FILES
        src/dispatcher.cpp
        src/socket.cpp
        header/dispatcher.h
        header/socket.h
        header/util.h)

set(ENDUSER_SOURCE_FILES
        src/end-user.cpp
        src/socket.cpp
        header/end-user.h
        header/socket.h
        header/util.h)

add_executable(Dispatcher ${DISPTACHER_SOURCE_FILES})

add_executable(EndUser ${ENDUSER_SOURCE_FILES})