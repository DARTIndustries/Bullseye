//Servo Controller 
//November 2018 
//DART
#pragma once
//find lib for servo 
#include <commands/AbstractCommand.h>
#include <drivers/AbstractPwmDriver.h>
#include "AbstractController.h"

class ServoController: public ServoController {
public:
	ServoController(AbstractPwmDriver* pwm_driver);
	void execute(ServoCommand* cmd);
private:
	AbstractPwmDriver* pwm;
}

	