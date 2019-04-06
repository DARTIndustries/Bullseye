//Shared Memory Driver
//3/16/2019
//DART
//author: Adam
#pragma once

#define POSITION_SHM_KEY_ID 65
#define POSITION_SHM_FILE "/var/shm/position.shm"


/** This struct is stored in shared memory that is mapped by both the robot and location processes */
typedef struct {
	/* The id fields are used as debug flags for synchronization. 
		motor_values_id=0 message matches up with the position_vect_id=0 message. 
		The code will never use these for synchronization (we don't really care), but 
		it is nice to see if one is falling behind the other, maybe even log about it. 

		The idea being that position_vect_id is incremented linearly and motor_values_id is a 
		snapshot of the position_vect_id that its calculation is based on. 
	*/

	/* These values are written only by the robot main process. They are read by location */
	unsigned int position_vect_id;
	double position_vect[3];

	/* These values are written only by the location process. They are read by robot */
	unsigned int motor_values_id;
	double motor_values[8];
} location_shm_t;

class SharedMemoryDriver {
public:
	/** Returns a pointer to a shared memory map. This pointer can freely be written to without locks */
	volatile location_shm_t *open_location_shm();

	/** This method detaches your process from the shared memory. 
	   This call is not required as it will be detached when the process exits */
	void detach_location_shm(location_shm_t * shm);

	/** This call destroys the shared memory. 
	   It should only be called if all process are done with the shared memory
	   This call is not required because the same map will be reused if it is not destroyed. 
	*/
	void destroy_location_shm();

};
