#pragma once

#include<commands/CommandType.h>
#include<stdint.h>


#pragma pack(push, 1)
struct ServoCommand {
	uint32_t type = (uint32_t)CommandType::SERVO_COMMAND; //CommandType 
	double position;
	unsigned short servoNum; 
};
#pragma pack(pop)