#include <iostream>
#include <drivers/NetworkingDriver.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <commands/CommandUnion.h>
#include <commands/LedCommand.h>
#include <commands/ServoCommand.h>
#include <commands/AbstractCommand.h>
#include <thread>
#include <unistd.h>

//thread that sends "robot status"(struct) to client
void heartbeat_thread(NetworkingDriver net_driver){
    std::cout << "Heartbeat thread started up " << std::endl;
    try {
        while(true) {

            LedCommand led;
            led.b = 5;
            led.r = 1;
            led.g = 255;

            net_driver.send_packet(&led, sizeof(led));
            sleep(1);
        }
    } catch (const char* msg){
        std::cout << "Heartbeat thread: " << msg << std::endl;
    }
    std::cout << "Heartbeat exiting " << std::endl;
}

int main(int argc, char const *argv[]) {
    char buffer[1024] = {0};
    NetworkingDriver net_driver;
    CommandUnion commUnion;

    //Accept loop
    while(true) {
        
        std::cout << "Listening on localhost:8000 " << std::endl;
        net_driver.open_connection();
        std::cout << "Client Connected " << std::endl;

        std::thread heartbeat(heartbeat_thread, net_driver);
        
        try {
            //Receive messages loop
            while(true) {

                int bytes_read = net_driver.read_packet (buffer, sizeof (buffer));

                std::cout << "READ: " << buffer << "\n";
                
                //read in first few bytes to get id, set id of union to that and then use the switch statement to determine what the shit is

                // AbstractCommand *comm = (AbstractCommand*)buffer;
                // //adding to union
                // switch(*comm->type){
                //     case (uint32_t)CommandType::LED_COMMAND : 
                //         commUnion->led = *comm;
                //         break;
                //     case (uint32_t)CommandType::SERVO_COMMAND :
                //         commUnion->servo = *comm;
                //         break;
                // }

                printf("Red: %u\n", commUnion.led->r);
                printf("Green: %u\n", commUnion.led->g);
                printf("Blue: %u\n", commUnion.led->b);

            }
        } catch (const char* msg) {
            std::cout << "Main: " << msg << std::endl;
        }

        std::cout << "Waiting for heartbeat thread to exit " << std::endl;
        heartbeat.join();

    }

    return 0; 
} 

