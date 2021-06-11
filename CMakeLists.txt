cmake_minimum_required(VERSION 3.13.4)

set(CMAKE_CXX_STANDARD 17)

project(LibGraphics)

if(WIN32)
    set(PLATFORM windows)
endif()

add_library(
    ${PROJECT_NAME} 
    include/${PROJECT_NAME}/window.h 
    include/${PROJECT_NAME}/standard_string.h
    include/${PROJECT_NAME}/string.h
    ${PLATFORM}/include/standard_string_${PLATFORM}.h
    ${PLATFORM}/opengl/source/window.cpp
    ${PLATFORM}/source/standard_string_${PLATFORM}.cpp
    ${PLATFORM}/source/string.cpp)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} Kernel32.lib)
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
