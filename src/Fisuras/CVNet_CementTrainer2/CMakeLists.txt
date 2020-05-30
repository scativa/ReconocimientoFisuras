cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(CVNet_CementTrainer2)

find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

target_precompile_headers(myTarget
  PUBLIC
    pch.h
)

add_executable(CVNet_CementTrainer2 CementTrainer.cpp CVNet_CementTrainer2.cpp pch.cpp  cmdlineopt.cpp)
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
