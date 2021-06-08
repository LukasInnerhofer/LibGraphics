cmake_minimum_required(VERSION 3.13.4)

project(LibGraphics)

if(WIN32)
    set(PLATFORM windows)
endif()

add_library(${PROJECT_NAME} 
    include/window.h 
    source/${PLATFORM}/opengl/window.cpp)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} Kernel32.lib)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE include)

option(TEST "Build a test executable" OFF)

if(TEST)
    add_subdirectory(test)
endif()
