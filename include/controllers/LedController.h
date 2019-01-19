//LED Contoroller
//11/17/2018
//DART
//author: Gurleen and Kenneth
#pragma once

#include"AbstractController.h"
#include<commands/AbstractCommand.h>
#include<drivers/AbstractPwmDriver.h>
#include<commands/LedCommand.h>

// template <typename AbstractPwmDriver_t>
#define RED_PIN 12
#define GREEN_PIN 13
#define BLUE_PIN 14


class LedController {
public:
    LedController(AbstractPwmDriver* pwmDriver);
    void execute(LedCommand* command);
private:
    AbstractPwmDriver* _pwmDriver;

};