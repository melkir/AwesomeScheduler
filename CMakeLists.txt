cmake_minimum_required(VERSION 3.4)
project(AwesomeScheduler)

include_directories(header)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/Process.cpp src/Scheduler.cpp src/RRStrategy.cpp src/FCFSStrategy.cpp)
set(HEADER_FILES header/Process.h header/SchedulingStrategy.h header/RRStrategy.h header/Scheduler.h header/FCFSStrategy.h)

add_executable(AwesomeScheduler ${SOURCE_FILES} ${HEADER_FILES})