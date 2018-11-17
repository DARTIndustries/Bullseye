//Adafruit 16Ch PWM Hat Driver
//11/10/2018
//DART
//author: Adam (everyone)

#pragma once
#include "../lib/PCA9685.h"
#include "AbstractPwmDriver.h"
#define MAX_PWM_DURATION 4091

class Adafruit16ChPwmHatDriver: public AbstractPwmDriver {
public:
	Adafruit16ChPwmHatDriver(int bus, int address);
	void setFrequency(int frequency);
	void setDutyCycle(int port, double percentDutyCycle);
private:
	PCA9685 _pwm;

};

