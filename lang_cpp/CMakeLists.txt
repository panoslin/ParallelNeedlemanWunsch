cmake_minimum_required(VERSION 3.24)
project(lang_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the MPI package
find_package(MPI REQUIRED)

include_directories(${MPI_INCLUDE_PATH})

#add_executable(lang_cpp pipeline.cpp testcases.cpp)
add_executable(lang_cpp serial.cpp testcases.cpp pipeline.cpp testcases.h)

# Link MPI libraries
target_link_libraries(lang_cpp PRIVATE MPI::MPI_CXX)
