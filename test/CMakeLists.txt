cmake_minimum_required(VERSION 3.13.4)

set(EXECUTABLE_NAME lib_graphics_test)
add_executable(${EXECUTABLE_NAME} main.cpp)

get_target_property(LIB_GRAPHICS_INCLUDE_DIRECTORIES lib_graphics INCLUDE_DIRECTORIES)
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${LIB_GRAPHICS_INCLUDE_DIRECTORIES})

target_link_libraries(${EXECUTABLE_NAME} ${PROJECT_NAME})

install(TARGETS ${EXECUTABLE_NAME} RUNTIME DESTINATION bin)