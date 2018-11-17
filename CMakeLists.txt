cmake_minimum_required(VERSION 3.10)
project(Bullseye)

set(CMAKE_CXX_STANDARD 17)

add_executable(Bullseye src/robot.cpp src/lib/PCA9685.cpp src/drivers/Adafruit16ChPwmHatDriver.cpp)
target_include_directories(Bullseye PRIVATE include)
