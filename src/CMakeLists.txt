cmake_minimum_required(VERSION 2.8)
project(tanks)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON) #...without compiler extensions like gnu++11
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Threads)
if(Threads)
    message("Threads found!")
endif()

add_subdirectory("${CMAKE_SOURCE_DIR}/../core" "${CMAKE_BINARY_DIR}/core")

add_executable(run run.cpp Tank.cpp PainterTanks.cpp helpers.cpp Brain.cpp ${SOURCES})
target_include_directories(run PUBLIC "${CMAKE_SOURCE_DIR}/../core")
target_link_libraries(run Core)
