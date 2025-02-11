cmake_minimum_required(VERSION 3.24.2)
project(ProjectFile)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ProjectFile
        Main2.cpp
        Professor.cpp
        Professor.h
        Student.cpp
        Student.h

        )
