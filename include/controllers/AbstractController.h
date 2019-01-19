//Abstract Controller
//11/10/2018
//DART
//author: Adam (everyone)

#pragma once

#include<commands/AbstractCommand.h>
#include<stdexcept>

class AbstractController {
public:
	virtual void execute(AbstractCommand command);
};

