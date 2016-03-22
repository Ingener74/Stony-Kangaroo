cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules")

find_package(Gloox REQUIRED)

add_definitions(-std=c++11)
include_directories(
        include
        ${GLOOX_INCLUDE_DIR}
)

set(SOURCES
        src/Logger.h
        src/Logger.cpp
        src/Output.h
        src/Output.cpp
        src/PrintfBuffer.cpp src/PrintfBuffer.h src/XmppBuffer.cpp src/XmppBuffer.h)
add_library(Logger ${SOURCES})

set(SOURCES
    src/LoggerTest.cpp
)
add_executable(LoggerTest ${SOURCES})
target_link_libraries(LoggerTest Logger ${GLOOX_LIBRARIES})