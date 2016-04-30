cmake_minimum_required(VERSION 3.4)
project(AwesomeScheduler)

include_directories(header)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(SOCKET_SOURCE_FILES
        src/socket.cpp
        header/socket.h
        header/util.h)

set(DISPTACHER_SOURCE_FILES
        src/dispatcher.cpp
        header/dispatcher.h)

set(ENDUSER_SOURCE_FILES
        src/end-user.cpp
        header/end-user.h)

set(TASKPROPERTIES_SOURCE_FILES
        src/task_properties.cpp
        header/task_properties.h)

add_executable(Dispatcher ${SOCKET_SOURCE_FILES} ${DISPTACHER_SOURCE_FILES})

add_executable(EndUser ${SOCKET_SOURCE_FILES} ${ENDUSER_SOURCE_FILES} ${TASKPROPERTIES_SOURCE_FILES})
target_link_libraries(EndUser ${Boost_LIBRARIES})