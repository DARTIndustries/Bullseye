// pwmDebug.cpp
#define ROBOT_MODE 1
#include <iostream>
#if ROBOT_MODE 
	#include <drivers/AbstractPwmDriver.h>
	#include <drivers/Adafruit16ChPwmHatDriver.h>
#else
	#include <drivers/MockPwmDriver.h>
#endif 
int main() {
    int pin;
    double val;
    std::cout << "Enter pin: ";
    std::cin >> pin;
#if ROBOT_MODE
    auto pwmDriver = Adafruit16ChPwmHatDriver(1, 0x40); // TODO: Make the 1 a macro
#else
	auto pwmDriver = MockPwmDriver(1, 0x40);
#endif
	pwmDriver.setFrequency(60);
    while(true) {
        std::cout << "Enter duty cycle: ";
        std::cin >> val;
        if (val < -1 || val > 1) {
            std::cout << "Error! val out of bounds!";
            continue;
        }
	    pwmDriver.setDutyCycle(pin, val);
    }
    return 0;
}