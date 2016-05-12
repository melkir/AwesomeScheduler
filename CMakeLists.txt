cmake_minimum_required(VERSION 3.4)
project(AwesomeScheduler)

include_directories(header)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(Boost REQUIRED COMPONENTS system filesystem)
include_directories(${Boost_INCLUDE_DIRS})

set(SOCKET_SOURCE_FILES
        src/socket.cpp
        header/socket.h
        header/util.h)

set(TASKPROPERTIES_SOURCE_FILES
        src/task_properties.cpp
        header/task_properties.h)

set(DISPTACHER_SOURCE_FILES
        ${TASKPROPERTIES_SOURCE_FILES}
        ${SOCKET_SOURCE_FILES}
        src/dispatcher.cpp
        header/dispatcher.h)

set(ENDUSER_SOURCE_FILES
        ${TASKPROPERTIES_SOURCE_FILES}
        ${SOCKET_SOURCE_FILES}
        src/end-user.cpp
        header/end-user.h)

set(WORKER_SOURCE_FILES
        ${TASKPROPERTIES_SOURCE_FILES}
        ${SOCKET_SOURCE_FILES}
        src/worker.cpp
        header/worker.h)

add_executable(Dispatcher ${DISPTACHER_SOURCE_FILES})
target_link_libraries(Dispatcher ${Boost_LIBRARIES})

add_executable(EndUser ${ENDUSER_SOURCE_FILES})
target_link_libraries(EndUser ${Boost_LIBRARIES})

add_executable(Worker ${WORKER_SOURCE_FILES})
target_link_libraries(Worker ${Boost_LIBRARIES})