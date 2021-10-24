cmake_minimum_required(VERSION 3.13.4)

set(CMAKE_CXX_STANDARD 20)

project(libgraphics)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(PLATFORM "windows")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(PLATFORM "linux")
endif()

add_library(
    ${PROJECT_NAME}
    include/${PROJECT_NAME}/color.h
    include/${PROJECT_NAME}/drawable.h
    include/${PROJECT_NAME}/drawable_vertex_buffer.h
    include/${PROJECT_NAME}/rectangle.h
    include/${PROJECT_NAME}/string.h
    include/${PROJECT_NAME}/texture.h
    include/${PROJECT_NAME}/vector.h
    include/${PROJECT_NAME}/vertex_buffer.h
    include/${PROJECT_NAME}/vertex.h
    include/${PROJECT_NAME}/window.h
    source/color.cpp
    source/drawable.cpp
    source/drawable_vertex_buffer.cpp
    source/rectangle.cpp
    source/string.cpp
    source/texture.cpp
    source/vertex_buffer.cpp
    source/${PLATFORM}/opengl/opengl_${PLATFORM}.h
    source/${PLATFORM}/opengl/opengl_${PLATFORM}.cpp
    source/${PLATFORM}/opengl/window_impl.cpp
    source/opengl/opengl_drawable.cpp
    source/opengl/opengl_drawable.h
    source/opengl/opengl.cpp
    source/opengl/opengl.h
    source/opengl/shader_program.h
    source/opengl/shader.cpp
    source/opengl/shader.h
    source/opengl/window_impl.h
    source/opengl/window.cpp)

get_target_property(LIBUTILITIES_INCLUDE_DIRECTORIES libutilities INCLUDE_DIRECTORIES)
target_include_directories(${PROJECT_NAME} PUBLIC ${LIBUTILITIES_INCLUDE_DIRECTORIES})

if(${PLATFORM} STREQUAL "windows")
    target_link_libraries(${PROJECT_NAME} Kernel32.lib)
elseif(${PLATFORM} STREQUAL "linux")
    target_link_libraries(${PROJECT_NAME} pthread)
    target_link_libraries(${PROJECT_NAME} X11)
    target_link_libraries(${PROJECT_NAME} GL)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC include)

option(LIBGRAPHICS_PRINT_GL_ERRORS "Print errors of the underlying graphics library to stderr" OFF)

if(DEFINED LIBGRAPHICS_INSTALL_PATH)
    install(
        FILES 
        ${CMAKE_CURRENT_SOURCE_DIR}/source/opengl/shaders/vertex.glsl
        ${CMAKE_CURRENT_SOURCE_DIR}/source/opengl/shaders/vertex_texture.glsl
        ${CMAKE_CURRENT_SOURCE_DIR}/source/opengl/shaders/fragment.glsl
        ${CMAKE_CURRENT_SOURCE_DIR}/source/opengl/shaders/fragment_texture.glsl
        DESTINATION ${LIBGRAPHICS_INSTALL_PATH})
else()
    message(WARNING "No install path specified.")
endif()

if(LIBGRAPHICS_PRINT_GL_ERRORS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LIBGRAPHICS_PRINT_GL_ERRORS=1)
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE LIBGRAPHICS_PRINT_GL_ERRORS=0)
endif()
