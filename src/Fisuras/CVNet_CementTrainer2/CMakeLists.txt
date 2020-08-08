# CVNet_CementTrainer2
#
# cmake -DCMAKE_PREFIX_PATH=/home/seba/libtorch -DCMDLINEOPT_PATH=/home/seba/Repositories/cmdlineopt ..
# cmake --build . --config Debug


cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(CVNet_CementTrainer2)

find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(CVNet_CementTrainer2 CementTrainer.cpp CVNet_CementTrainer2.cpp ${CMDLINEOPT_PATH}/include/cmdlineopt.hpp ../common/globals.cpp)

# Precompiled header pch.h
target_precompile_headers(CVNet_CementTrainer2 PUBLIC pch.h)

# Muestra el tiempo de compilación de cada archivo
set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")

target_link_libraries(CVNet_CementTrainer2 "${TORCH_LIBRARIES}")
set_property(TARGET CVNet_CementTrainer2 PROPERTY CXX_STANDARD 14)

# The following code block is suggested to be used on Windows.
# According to https://github.com/pytorch/pytorch/issues/25457,
# the DLLs need to be copied to avoid memory errors.
if (MSVC)
  file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
  add_custom_command(TARGET CVNet_CementTrainer2
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
                     ${TORCH_DLLS}
                     $<TARGET_FILE_DIR:torch-test>)
endif (MSVC)
