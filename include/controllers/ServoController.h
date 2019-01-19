//Servo Controller 
//November 2018 
//DART
#pragma once
//find lib for servo 
#include <commands/AbstractCommand.h>
#include <drivers/AbstractPwmDriver.h>
#include <commands/ServoCommand.h>
#include <controllers/AbstractController.h>

#define FREQ 60

#define VERT_PIN 8
#define HORZ_PIN 9

class ServoController{
public:
	ServoController(AbstractPwmDriver* pwm_driver, double low, double mid, double high);
	void execute(ServoCommand* cmd);
private:
	AbstractPwmDriver* _pwmDriver;
	double _low;
	double _mid;
	double _high;
};