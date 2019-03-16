cmake_minimum_required(VERSION 3.9.2)
project(SharedMemoryTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(SharedMemoryTest src/SharedMemoryDriver.cpp )
target_include_directories(SharedMemoryTest PRIVATE include)
