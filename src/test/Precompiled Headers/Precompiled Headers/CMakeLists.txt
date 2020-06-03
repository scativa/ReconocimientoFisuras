# Test PRECOMPILED HEADERS
#
# cmake -S .. -B .
# cmake --build . --config Debug


cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(PrecompiledHeader)


add_executable(PrecompiledHeader Main.cpp)

# Precompiled header pch.h
target_precompile_headers(PrecompiledHeader PUBLIC pch.h)

# Muestra el tiempo de compilación de cada archivo
# set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(TARGET PrecompiledHeader PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")

set_property(TARGET PrecompiledHeader PROPERTY CXX_STANDARD 14)

