
#include <drivers/NetworkingDriver.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<commands/LedCommand.h>

int main(int argc, char const *argv[]) {
    char buffer[1024];

    NetworkingDriver net_driver;

    net_driver.open_connection();
    net_driver.read_packet(buffer, sizeof(buffer));

    printf("READ: %s\n", buffer);

    LedCommand led;

    led.b = 5;
    led.r = 50;
    led.g = 240;

    net_driver.send_packet(&led, sizeof(led));


    //TODO: Close?

    // send(new_socket , hello , strlen(hello) , 0 ); 
    // printf("Hello message sent\n"); 
    return 0; 
} 



//TODO: Move to driver code


