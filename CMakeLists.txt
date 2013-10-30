cmake_minimum_required(VERSION 2.6)
project(libkipr_link_depth_sensor)

set(BUILD_SHARED_LIBS ON)

include_directories(include)

add_library(kipr_link_depth_sensor src/depth_c.cpp
                                   src/Depth.cpp
                                   src/AsusXtionDepthDriver.cpp)

add_executable(display_center_distance examples/display_center_distance)
target_link_libraries(display_center_distance kipr_link_depth_sensor)
