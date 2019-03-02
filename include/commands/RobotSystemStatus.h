#include<stdint.h>
#include<commands/CommandType.h>

#pragma pack(push, 1)
struct RobotSystemStatus {
	uint32_t type = (uint32_t)CommandType::ROBOT_SYSTEM_STATUS; //CommandType 
	double percentCpu;
};
#pragma pack(pop)