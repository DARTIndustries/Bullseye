#include <controllers/ServoController.h>
#include <drivers/Adafruit16ChPwmHatDriver.h>

ServoController::ServoController(AbstractPwmDriver* pwm_driver) {
	_pwmDriver = pwm_driver; 
	_pwmDriver->setFrequency(FREQ);
}

void ServoController::execute(ServoCommand* cmd) {
	double pos = cmd->position;
	_pwmDriver->setDutyCycle(VERT_PIN, this.setValue(pos));
}

double ServoController::setValue(double value){
	double outVal = 0; 
	
	if(value > 1 || value < -1){
		throw std::invalid_argument("Value out of bounds, [-1, 1]"); 
	}

	/*==Scale the input using a piecewise function===
	 0 = mid
	 then  0 -> 1 scale linearly to mid->upper
	 then - 1 -> 0 scale linearly to lower->mid
	*/

	if (value > 0){
		outVal = (value * (UPPER - MID)) + MID;
	}
	else {
		outVal = (value * (MID - LOWER)) + MID;
	}

	return outVal; 
}