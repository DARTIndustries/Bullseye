cmake_minimum_required(VERSION 3.9.2)
project(Bullseye)

set(CMAKE_CXX_STANDARD 17)

aux_source_directory(src src_dir)

#add_executable(Bullseye src/robot.cpp src/lib/PCA9685.cpp src/drivers/Adafruit16ChPwmHatDriver.cpp src/commands/LedCommand.cpp src/controllers/LedController.cpp src/controllers/ServoController.cpp)
add_executable(Bullseye ${src_dir})
target_include_directories(Bullseye PRIVATE include)

