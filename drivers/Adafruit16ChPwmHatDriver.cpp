//Adafruit 16Ch PWM Hat Driver
//11/10/2018
//DART
//author: Adam (everyone)

#include "Adafruit16ChPwmHatDriver.h"
#include "../lib/PCA9685.h"

Adafruit16ChPwmHatDriver::Adafruit16ChPwmHatDriver(int bus, int address) {
	_pwm.init(bus, address);
}

void Adafruit16ChPwmHatDriver::setFrequency(int frequency) {
	_pwm.setPWMFreq(frequency);
}

void Adafruit16ChPwmHatDriver::setDutyCycle(int port, double percentDutyCycle) {
	_pwm.setPWM(port, static_cast<int>(MAX_PWM_DURATION * percentDutyCycle));
}

