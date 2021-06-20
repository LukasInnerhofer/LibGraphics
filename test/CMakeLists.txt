cmake_minimum_required(VERSION 3.13.4)

add_executable(${PROJECT_NAME}_test main.cpp)

target_include_directories(${PROJECT_NAME}_test PRIVATE ../include)

target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})