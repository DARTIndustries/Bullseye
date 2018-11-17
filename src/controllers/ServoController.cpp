#include"ServoController.h"
#include <drivers/Adafruit16ChPwmHatDriver.h>

ServoController::ServoController(AbstractPwmDriver* pwm_driver) {
	pwm = pwm_driver; 
}

ServoController::execute(ServoCommand* cmd) {
	double pos = cmd->position;

}