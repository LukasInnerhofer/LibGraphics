cmake_minimum_required(VERSION 3.13.4)

add_executable(${PROJECT_NAME}Test main.cpp)

target_include_directories(${PROJECT_NAME}Test PRIVATE ../include)

target_link_libraries(${PROJECT_NAME}Test LibGraphics)