#include <iostream> 
#include <stdio.h>
#include <sys/types.h> 
#include <SharedMemoryDriver.h>
#include <unistd.h> 

int main (int argc, char* argv[]) {
    SharedMemoryDriver shm_driver;

    printf("Sharedmem startup");

    if (fork() == 0) {
        /* Child (gyro: read position, write motor) */
        printf("Child fork opening shm\n");
        volatile location_shm_t* loc_shm = shm_driver.open_location_shm();

        for(int i = 0; i < 50; i++) {
            printf("child|vect_id: %i\n", loc_shm->position_vect_id);
            printf("child|vect[0]: %f\n", loc_shm->position_vect[0]);
            printf("child|vect[1]: %f\n", loc_shm->position_vect[1]);
            printf("child|vect[2]: %f\n", loc_shm->position_vect[2]);

            loc_shm->motor_values_id = loc_shm->position_vect_id;
            loc_shm->motor_values[0] = loc_shm->position_vect[0];
            loc_shm->motor_values[1] = loc_shm->position_vect[1];
            loc_shm->motor_values[2] = loc_shm->position_vect[2];
        }

    } else {
        /* Parent (robot: write position, read read motor) */
        printf("Parent fork opening shm\n");
        volatile location_shm_t* loc_shm = shm_driver.open_location_shm();

        for(int i = 0; i < 50; i++) {
            loc_shm->position_vect_id = i;
            loc_shm->position_vect[0] = i + 1;
            loc_shm->position_vect[1] = i + 2;
            loc_shm->position_vect[2] = i + 3;

            printf("parent|motor_id: %i\n", loc_shm->motor_values_id);
            printf("parent|motor[0]: %f\n", loc_shm->motor_values[0]);
            printf("parent|motor[1]: %f\n", loc_shm->motor_values[1]);
            printf("parent|motor[2]: %f\n", loc_shm->motor_values[2]);
        }
    }

    return 0;
}