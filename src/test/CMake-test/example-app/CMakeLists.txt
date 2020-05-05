cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(example-app)

message("CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}")
message("CMAKE_MODULE_PATH=${CMAKE_MODULE_PATH}")

# message("--- CMAKE_CXX_FLAGS ---")
# message("${CMAKE_CXX_FLAGS}")

find_package(Torch REQUIRED )

message("TORCH_FOUND=${TORCH_FOUND}")
message("TORCH_INCLUDE_DIR=${TORCH_INCLUDE_DIR}")
message("TORCH_LIBRARIES=${TORCH_LIBRARIES}")
message("TORCH_DIRECTORIES=${TORCH_DIRECTORIES}")
message("TORCH_CXX_FLAGS=${TORCH_CXX_FLAGS}")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(example-app example-app.cpp archadj.cpp)
target_link_libraries(example-app "${TORCH_LIBRARIES}")
set_property(TARGET example-app PROPERTY CXX_STANDARD 14)

# The following code block is suggested to be used on Windows.
# According to https://github.com/pytorch/pytorch/issues/25457,
# the DLLs need to be copied to avoid memory errors.
if (MSVC)
  message("-- MSVC(Windows) --")
  file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
  add_custom_command(TARGET example-app
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
                     ${TORCH_DLLS}
                     $<TARGET_FILE_DIR:example-app>)
endif (MSVC)
