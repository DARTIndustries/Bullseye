//Shared Memory Driver
//3/2/2019
//DART
//author: Adam

#include <iostream> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h>

#include <SharedMemoryDriver.h>

/** Returns a pointer to a shared memory map. This pointer can freely be written to without locks */
static volatile location_shm_t *SharedMemoryDriver::open_location_shm() {
    key_t key = ftok(POSITION_SHM_FILE, POSITION_SHM_KEY_ID);
    int shmid = shmget(key, 1024, 0666|IPC_CREAT);

    return (volatile location_shm_t*) shmat(shmid, (void*)0, 0);
}

/** Returns a pointer to a shared memory map. This pointer can freely be written to without locks */
static void SharedMemoryDriver::detach_location_shm(location_shm_t * shm) {
    shmdt(shm); 
}

/** This call destroys the shared memory. 
    It should only be called if all process are done with the shared memory
    This call is not required because the same map will be reused if it is not destroyed. 
*/
static void SharedMemoryDriver::destroy_location_shm() {
    key_t key = ftok(POSITION_SHM_FILE, POSITION_SHM_KEY_ID);
    int shmid = shmget(key, 1024, 0666|IPC_CREAT);
    shmctl(shmid, IPC_RMID, NULL);
}
