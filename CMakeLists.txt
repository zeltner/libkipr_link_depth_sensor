cmake_minimum_required(VERSION 2.6)
project(libkipr_link_depth_sensor)

set(OpenNI_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../OpenNI-Linux-x86-2.2/Include)
set(OpenNI_LIBRARIES OpenNI2)
set(OpenNI_LIBRARY_DIRS ${PROJECT_SOURCE_DIR}/../OpenNI-Linux-x86-2.2/Redist)

set(BUILD_SHARED_LIBS ON)

include_directories(include
                    ${OpenNI_INCLUDE_DIR})

link_directories(${OpenNI_LIBRARY_DIRS})

add_library(kipr_link_depth_sensor src/depth_c.cpp
                                   src/DepthDriver.cpp
                                   src/AsusXtionDepthDriver.cpp
                                   src/DepthMap.cpp)
target_link_libraries(kipr_link_depth_sensor ${OpenNI_LIBRARIES})

add_executable(display_center_distance examples/display_center_distance)
target_link_libraries(display_center_distance kipr_link_depth_sensor)
