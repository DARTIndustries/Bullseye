#include <iostream>
#include <drivers/AbstractPwmDriver.h>
#include <drivers/Adafruit16ChPwmHatDriver.h>
#include <commands/ServoCommand.h>
#include <controllers/ServoController.h>

int main() {
	/*
    std::cout << "WE ARE DART!" << std::endl;
    std::cout << "AND WE HAVE CI" << std::endl;
    std::cout << "AND WE HAVE BULLSEYE!" << std::endl;

	auto pwmDriver = Adafruit16ChPwmHatDriver(1, 0x40);

	pwmDriver.setFrequency(60);
	pwmDriver.setDutyCycle(12, 0.5);
	*/

	//Testing servo controller
	auto pwmDriver = Adafruit16ChPwmHatDriver(1, 0x40);

	ServoController servo = ServoController(&pwmDriver);
	ServoCommand com = ServoCommand();
	com.position = 0.5;

	servo.execute(&com);
    return 0;
}


