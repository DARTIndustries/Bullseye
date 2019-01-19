#include <controllers/ServoController.h>
#include <drivers/Adafruit16ChPwmHatDriver.h>

ServoController::ServoController(AbstractPwmDriver* pwm_driver, double low, double mid, double high) {
	_pwmDriver = pwm_driver; 
	_pwmDriver->setFrequency(FREQ);
	_low = low; 
	_mid = mid; 
	_high = high; 
}

void ServoController::execute(ServoCommand* cmd) {
	double pos = cmd->position;
	double dutyCycle = 0; 
	//pos is -1 to 1
	if (pos > 1 || pos < -1) {
		throw std::invalid_argument("Value out of bounds, [-1, 1]");
	}

	/*==Scale the input using a piecewise function===
	 0 = mid
	 then  0 -> 1 scale linearly to mid->upper
	 then - 1 -> 0 scale linearly to lower->mid
	*/

	if (pos > 0) {
		dutyCycle = (pos * (_high - _mid)) + _mid;
	}
	else {
		dutyCycle = (pos * (_mid - _low)) + _low;
	}
	_pwmDriver->setDutyCycle(cmd->servoNum, dutyCycle);

}

