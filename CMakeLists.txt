cmake_minimum_required(VERSION 3.13.4)

set(CMAKE_CXX_STANDARD 17)

project(LibGraphics)

if(WIN32)
    set(PLATFORM windows)
endif()

add_library(
    ${PROJECT_NAME} 
    include/${PROJECT_NAME}/window.h 
    include/${PROJECT_NAME}/string.h
    source/${PROJECT_NAME}/${PLATFORM}/standard_string.h
    source/${PROJECT_NAME}/${PLATFORM}/window.cpp
    source/${PROJECT_NAME}/${PLATFORM}/standard_string.cpp
    source/${PROJECT_NAME}/${PLATFORM}/string.cpp)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} Kernel32.lib Opengl32.lib)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PLATFORM}/include)

option(TEST "Build a test executable" OFF)
option(UNICODE "Enable unicode support" ON)

if(TEST)
    add_subdirectory(test)
endif()

if(UNICODE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE UNICODE)
endif()
