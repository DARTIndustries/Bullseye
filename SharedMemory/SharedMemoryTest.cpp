#include <iostream> 
#include <stdio.h>
#include <sys/types.h> 
#include <SharedMemoryDriver.h>
#include <unistd.h> 

int main (int argc, char* argv[]) {
    SharedMemoryDriver shm_driver;

    printf("Sharedmem startup");

    if (fork() == 0) {
        /* Child (gyro: read position) */
        printf("Child fork opening shm\n");
        volatile location_shm_t* loc_shm = shm_driver.open_location_shm();

        for(int i = 0; i < 50; i++) {
            printf("child|vect_id: %i\n", loc_shm->position_vect_id);
            for (int j = 0; j < 6; j++) {
                printf("child|vect[%i]: %f\n", j, loc_shm->position_vect[j]);
            }
        }

    } else {
        /* Parent (robot: write position) */
        printf("Parent fork opening shm\n");
        volatile location_shm_t* loc_shm = shm_driver.open_location_shm();

        for(int i = 0; i < 50; i++) {
            loc_shm->position_vect_id = i;
            for (int j = 0; j < 6; j++) {
                loc_shm->position_vect[j] = i + j;
            }
        }
    }

    return 0;
}
