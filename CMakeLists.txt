cmake_minimum_required(VERSION 3.16)
project(paint LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(paint 
    main.cpp 
    mainwindow.cpp 
    mainwindow.h
)
target_link_libraries(paint PRIVATE Qt6::Widgets)