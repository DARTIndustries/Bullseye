// Mock PWM Driver
// 1/14/2019
// DART
// author: Gurleen

#pragma once
#include "AbstractPwmDriver.h"

class MockPwmDriver: public AbstractPwmDriver {
public:
    MockPwmDriver(int bus, int address);
    void setFrequency(int frequency);
    void setDutyCycle(int port, double percentDutyCycle);
};