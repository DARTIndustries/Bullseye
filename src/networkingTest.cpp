#include <iostream>
#include <drivers/NetworkingDriver.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <commands/LedCommand.h>
#include <thread>

//thread that sends "robot status"(struct) to client
void heartbeat_thread(NetworkingDriver net_driver){
    std::cout << "heartbeat thread!\n";

    LedCommand led;

    led.b = 5;
    led.r = 1;
    led.g = 255;

    net_driver.send_packet(&led, sizeof(led));
}

int main(int argc, char const *argv[]) {
    char buffer[1024];

    NetworkingDriver net_driver;
    
    while(true){
        net_driver.open_connection();
        
        //spawn heartbeat thread
        // std::thread heartbeat (heartbeat_thread, net_driver);
        // std::cout << "main, foo and bar now execute concurrently...\n";
        // heartbeat.join();

        while(true){
            net_driver.read_packet(buffer, sizeof(buffer));

            std::cout << "READ: " << buffer << "\n";

            //example of struct being sent
            LedCommand led;

            led.b = 5;
            led.r = 1;
            led.g = 255;

            net_driver.send_packet(&led, sizeof(led));
        }
        
        // net_driver.close_connection();
    }
    
    


    //TODO: Close?

    // send(new_socket , hello , strlen(hello) , 0 ); 
    // printf("Hello message sent\n"); 
    return 0; 
} 

//TODO: Move to driver code


