cmake_minimum_required(VERSION 3.4)
project(AwesomeScheduler)

include_directories(header)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(DISPTACHER_SOURCE_FILES
        src/Dispatcher.cpp
        src/Socket.cpp
        header/Dispatcher.h
        header/Socket.h
        header/Util.h)

set(ENDUSER_SOURCE_FILES
        src/EndUser.cpp
        src/Socket.cpp
        header/EndUser.h
        header/Socket.h
        header/Util.h)

add_executable(Dispatcher ${DISPTACHER_SOURCE_FILES})

add_executable(Enduser ${ENDUSER_SOURCE_FILES})