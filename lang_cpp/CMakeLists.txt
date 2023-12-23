cmake_minimum_required(VERSION 3.24)
project(CPPTutorial)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the MPI package
find_package(MPI REQUIRED)

include_directories(${MPI_INCLUDE_PATH})

add_executable(CPPTutorial mpi_hello_world.cpp testcases.cpp testcases.h serial.cpp)

# Link MPI libraries
target_link_libraries(CPPTutorial PRIVATE MPI::MPI_CXX)
