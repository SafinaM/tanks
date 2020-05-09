cmake_minimum_required(VERSION 2.8)
project(tanks)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON) #...without compiler extensions like gnu++11
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Threads)
if(Threads_FOUND)
    message("Threads are found!")
else()
    message(FATAL_ERROR "Threads are not found!")
endif()

add_subdirectory("${CMAKE_SOURCE_DIR}/../core" "${CMAKE_BINARY_DIR}/core")

add_executable(run run.cpp Tank.cpp PainterTanks.cpp helpers.cpp Brain.cpp Ammo.cpp Map.cpp BaseAmmoTankFigure.cpp ${SOURCES} )
add_executable(test test.cpp Map.cpp Tank.cpp Ammo.cpp BaseAmmoTankFigure.cpp ${SOURCES})

target_include_directories(run PUBLIC "${CMAKE_SOURCE_DIR}/../core")
target_link_libraries(run Core ${CMAKE_THREAD_LIBS_INIT})

target_include_directories(test PUBLIC "${CMAKE_SOURCE_DIR}/../core")
target_link_libraries(test Core ${CMAKE_THREAD_LIBS_INIT})
