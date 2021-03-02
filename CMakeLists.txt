cmake_minimum_required(VERSION 3.17)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project(Simulatie)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Simulatie
        Declarations.h
        Filaments.h
        Functions.cpp
        main.cpp
        PARAMETERS.h)
