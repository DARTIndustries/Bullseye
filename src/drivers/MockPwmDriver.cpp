// Mock PWM Driver
// 1/14/2019
// DART
// author: Gurleen

#include <drivers/MockPwmDriver.h>
#include <iostream>

MockPwmDriver::MockPwmDriver(int bus, int frequency) {
    std::cout << "MockPwmDriver: initalized on bus " << bus << "\n";
}

void MockPwmDriver::setFrequency(int frequency) {
    std::cout << "MockPwmDriver: frequency set to " << frequency << "\n";
}

void MockPwmDriver::setDutyCycle(int port, double percentDutyCycle) {
    std::cout << "MockPwmDriver: duty cycle on port " << port << " set to " << percentDutyCycle;
}