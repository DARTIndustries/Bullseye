#include <controllers/ServoController.h>
#include <drivers/Adafruit16ChPwmHatDriver.h>

ServoController::ServoController(AbstractPwmDriver* pwm_driver) {
	_pwmDriver = pwm_driver; 
	_pwmDriver->setFrequency(FREQ);
}

void ServoController::execute(ServoCommand* cmd) {
	double pos = cmd->position;
	if(pos > 1 || pos < -1) {
		// TODO: Add exception
	}
	// Scale value from -1 to 1 to percentage
	pos = (pos + 1) / 2.0;
	_pwmDriver->setDutyCycle(VERT_PIN, pos);
}