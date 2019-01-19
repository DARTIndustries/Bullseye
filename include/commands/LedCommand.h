// LED Command
// 11/17/2018
// DART
// Authors: Gurleen and Kenneth

#pragma once

#include<commands/CommandType.h>
#include<stdint.h>

#pragma pack(push, 1)
struct LedCommand {
	uint32_t type; //CommandType 
	unsigned char r;
	unsigned char g;
	unsigned char b; 
};
#pragma pack(pop)