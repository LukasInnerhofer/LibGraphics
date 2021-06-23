cmake_minimum_required(VERSION 3.13.4)

set(CMAKE_CXX_STANDARD 20)

project(lib_graphics)

if(WIN32)
    set(PLATFORM windows)
endif()

add_library(
    ${PROJECT_NAME} 
    include/${PROJECT_NAME}/window.h 
    include/${PROJECT_NAME}/string.h
    source/${PROJECT_NAME}/string.cpp
    source/${PROJECT_NAME}/color.cpp
    source/${PROJECT_NAME}/${PLATFORM}/opengl.cpp
    source/${PROJECT_NAME}/${PLATFORM}/window.cpp)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} Kernel32.lib Opengl32.lib)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PLATFORM}/include)

option(TEST "Build a test executable" OFF)

if(TEST)
    add_subdirectory(test)
endif()
