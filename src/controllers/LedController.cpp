//LED Contoroller
//11/17/2018
//DART
//author: Gurleen and Kenneth

#include<controllers/LedController.h>

LedController::LedController(AbstractPwmDriver* pwmDriver) {
    _pwmDriver = pwmDriver;
}

void LedController::execute(LedCommand* command) {
	_pwmDriver->setDutyCycle(RED_PIN, command->r / 255);
    _pwmDriver->setDutyCycle(GREEN_PIN, command->g / 255);
    _pwmDriver->setDutyCycle(BLUE_PIN, command->b / 255);
}