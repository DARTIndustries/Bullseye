//Servo Controller 
//November 2018 
//DART
#pragma once
//find lib for servo 
#include <commands/AbstractCommand.h>
#include <drivers/AbstractPwmDriver.h>
#include <commands/ServoCommand.h>
#include "AbstractController.h"

#define FREQ 60

#define VERT_PIN 8
#define HORZ_PIN 9

#define LOWER 140
#define MID 332
#define UPPER 540

class ServoController: public AbstractController {
public:
	ServoController(AbstractPwmDriver* pwm_driver);
	void execute(ServoCommand* cmd);
	double setValue(double value); 
private:
	AbstractPwmDriver* _pwmDriver;
};