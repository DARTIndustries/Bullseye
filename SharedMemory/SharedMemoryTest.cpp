#include <iostream> 
#include <stdio.h>

#include <SharedMemoryDriver.h>


int main (int argc, char* argv[]) {

    printf("Sharedmem startup");
    SharedMemoryDriver shm_driver;

    volatile location_shm_t* loc_shm = shm_driver.open_location_shm();

    printf("Vect_id: %i\n", loc_shm->position_vect_id);
    printf("vect[0]: %f\n", loc_shm->position_vect[0]);
    printf("vect[1]: %f\n", loc_shm->position_vect[1]);
    printf("vect[2]: %f\n", loc_shm->position_vect[2]);

    loc_shm->position_vect_id = 0;
    loc_shm->position_vect[0] = 1;
    loc_shm->position_vect[1] = 2;
    loc_shm->position_vect[2] = 3;

    return 0;
}