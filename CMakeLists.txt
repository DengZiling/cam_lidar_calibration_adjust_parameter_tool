cmake_minimum_required(VERSION 3.5)

project(cam_lidar_calibration LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加Eigen头文件
include_directories("/usr/include/eigen3")

find_package(Qt5Core)

add_executable(cam_lidar_calibration
  main.cpp
)
target_link_libraries(cam_lidar_calibration Qt5::Core)
