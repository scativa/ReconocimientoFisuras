cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(opencv-test)

find_package(OpenCVGen REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(opencv-test opencv-test.cpp)
target_link_libraries(opencv-test "${OPENCV_LIBRARIES}")
set_property(TARGET opencv-test PROPERTY CXX_STANDARD 14)


