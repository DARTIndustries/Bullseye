//Abstract PWM Driver
//11/10/2018
//DART
//author: Adam (everyone)

#pragma once

class AbstractPwmDriver {
public:
	virtual void setFrequency(int frequency) = 0;
	virtual void setDutyCycle(int port, double percentDutyCycle) = 0;
};

