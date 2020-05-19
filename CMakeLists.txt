cmake_minimum_required(VERSION 2.8.9)
project(QtAS6)

set(CMAKE_AUTOMOC ON)
SET(CMAKE_CXX_FLAGS "-std=c++14")
find_package(Qt5Widgets REQUIRED)

include_directories(${Qt5Widgets_INCLUDES})
add_definitions(${Qt5Widgets_DEFINITIONS})


add_executable(QtAS6 main.cpp mainwidget.cpp imagewidget.cpp brush.cpp)

target_link_libraries(QtAS6 ${Qt5Widgets_LIBRARIES})
