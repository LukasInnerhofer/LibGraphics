cmake_minimum_required(VERSION 3.13.4)

set(CMAKE_CXX_STANDARD 20)

project(lib_graphics)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(PLATFORM "windows")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(PLATFORM "linux")
endif()

add_library(
    ${PROJECT_NAME} 
    include/${PROJECT_NAME}/canvas.h
    include/${PROJECT_NAME}/color.h
    include/${PROJECT_NAME}/drawable.h
    include/${PROJECT_NAME}/drawable_vertex_buffer.h
    include/${PROJECT_NAME}/rectangle.h
    include/${PROJECT_NAME}/string.h
    include/${PROJECT_NAME}/vector.h
    include/${PROJECT_NAME}/vertex_buffer.h 
    include/${PROJECT_NAME}/window.h 
    source/${PROJECT_NAME}/canvas.cpp
    source/${PROJECT_NAME}/color.cpp
    source/${PROJECT_NAME}/drawable.cpp
    source/${PROJECT_NAME}/drawable_vertex_buffer.cpp
    source/${PROJECT_NAME}/rectangle.cpp
    source/${PROJECT_NAME}/string.cpp
    source/${PROJECT_NAME}/vertex_buffer.cpp
    source/${PROJECT_NAME}/${PLATFORM}/opengl/opengl_${PLATFORM}.h
    source/${PROJECT_NAME}/${PLATFORM}/opengl/opengl_${PLATFORM}.cpp
    source/${PROJECT_NAME}/${PLATFORM}/opengl/window_impl.cpp
    source/${PROJECT_NAME}/opengl/opengl.cpp
    source/${PROJECT_NAME}/opengl/window_impl.h
    source/${PROJECT_NAME}/opengl/window.cpp)

if(${PLATFORM} STREQUAL "windows")
    target_link_libraries(${PROJECT_NAME} Kernel32.lib)
elseif(${PLATFORM} STREQUAL "linux")
    target_link_libraries(${PROJECT_NAME} pthread)
    target_link_libraries(${PROJECT_NAME} X11)
    target_link_libraries(${PROJECT_NAME} GL)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE include)

option(LIB_GRAPHICS_TEST "Build a test executable" OFF)
option(LIB_GRAPHICS_PRINT_GL_ERRORS "Print errors of the underlying graphics library to stderr" OFF)

if(LIB_GRAPHICS_TEST)
    add_subdirectory(test)
endif()

if(LIB_GRAPHICS_PRINT_GL_ERRORS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LIB_GRAPHICS_PRINT_GL_ERRORS=1)
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE LIB_GRAPHICS_PRINT_GL_ERRORS=0)
endif()
