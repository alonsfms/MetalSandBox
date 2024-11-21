cmake_minimum_required(VERSION 3.5.0)
project(MetalBaseLine VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

# include inc
add_subdirectory(metal-cmake) 

# add executables manually
add_executable(MetalBaseLine WIN32 src/main.cpp)

# link against glfw and OpenGL::GL
target_link_libraries(MetalBaseLine METAL_CPP)