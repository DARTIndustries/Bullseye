cmake_minimum_required(VERSION 3.9.2)
project(Bullseye)
project(pwmDebug)
project(networkingTest)
project(networkingClientTester)

set(CMAKE_CXX_STANDARD 17)

#aux_source_directory(src src_dir)

add_executable(Bullseye src/robot.cpp src/lib/PCA9685.cpp src/drivers/Adafruit16ChPwmHatDriver.cpp src/drivers/MockPwmDriver.cpp  src/controllers/LedController.cpp src/controllers/ServoController.cpp)
add_executable(pwmDebug src/pwmDebug.cpp src/lib/PCA9685.cpp src/drivers/Adafruit16ChPwmHatDriver.cpp src/drivers/MockPwmDriver.cpp  src/controllers/LedController.cpp src/controllers/ServoController.cpp)
add_executable(networkingTest src/networkingTest.cpp src/controllers/LedController.cpp src/controllers/ServoController.cpp src/drivers/NetworkingDriver.cpp)
add_executable(networkingClientTester src/networkingClientTester.cpp src/controllers/LedController.cpp src/controllers/ServoController.cpp )
#add_executable(Bullseye ${src_dir})
target_include_directories(Bullseye PRIVATE include)
target_include_directories(pwmDebug PRIVATE include)
target_include_directories(networkingTest PRIVATE include)
target_include_directories(networkingClientTester PRIVATE include)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Bullseye Threads::Threads)
target_link_libraries(networkingTest Threads::Threads)