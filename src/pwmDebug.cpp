// pwmDebug.cpp

#include <iostream>
#include <drivers/MockPwmDriver.h>
// #include <drivers/AbstractPwmDriver.h>
// #include <drivers/Adafruit16ChPwmHatDriver.h>

int main() {
    int pin;
    double val;
    std::cout << "Enter pin: ";
    std::cin >> pin;
    // auto pwmDriver = Adafruit16ChPwmHatDriver(1, 0x40); // TODO: Make the 1 a macro
    auto pwmDriver = MockPwmDriver(1, 0x40);
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