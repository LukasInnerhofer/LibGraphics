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
    include/${PROJECT_NAME}/color.h
    source/${PROJECT_NAME}/opengl.h
    source/${PROJECT_NAME}/window_impl.h
    source/${PROJECT_NAME}/string.cpp
    source/${PROJECT_NAME}/color.cpp
    source/${PROJECT_NAME}/window.cpp
    source/${PROJECT_NAME}/${PLATFORM}/opengl_${PLATFORM}.h
    source/${PROJECT_NAME}/${PLATFORM}/opengl_${PLATFORM}.cpp
    source/${PROJECT_NAME}/${PLATFORM}/window_impl.cpp)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} Kernel32.lib)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE ${PLATFORM}/include)

option(TEST "Build a test executable" OFF)

if(TEST)
    add_subdirectory(test)
endif()
