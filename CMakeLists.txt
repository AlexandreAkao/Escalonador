cmake_minimum_required(VERSION 3.15)
project(Escalonador)

set(CMAKE_CXX_STANDARD 14)

include_directories(Escalonador)

add_executable(Escalonador
        Escalonador/Core.hpp
        Escalonador/CPU.hpp
        Escalonador/Kernel.cpp
        Escalonador/Kernel.h
        Escalonador/MainScreen.cpp
        Escalonador/MainScreen.h
        Escalonador/Process.cpp
        Escalonador/Process.h
        Escalonador/Scheduler.hpp
        Escalonador/Simulador.cpp)
