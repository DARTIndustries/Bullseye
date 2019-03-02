
#include <drivers/NetworkingDriver.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char const *argv[]) {

    char buffer[1024];
    int num_read;
    int socket; 



    NetworkingDriver net_driver;

    net_driver.open_connection();
    net_driver.read_packet(buffer, sizeof(buffer));

    printf("READ: %s\n", buffer);
    net_driver.send_packet(buffer, strlen(buffer));



    //TODO: Close?

    // send(new_socket , hello , strlen(hello) , 0 ); 
    // printf("Hello message sent\n"); 
    return 0; 
} 



//TODO: Move to driver code


