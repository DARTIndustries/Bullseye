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

            // char* testMsg = "Hello World";

            net_driver.send_packet(&led, sizeof(led));
            // net_driver.send_packet(&testMsg, sizeof(testMsg));
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

    //Accept loop
    while(true) {
        
        std::cout << "Listening on localhost:8000 " << std::endl;
        net_driver.open_connection();
        std::cout << "Client Connected " << std::endl;

        std::thread heartbeat(heartbeat_thread, net_driver);
        
        try {
            //Receive messages loop
            while(true) {

				CommandUnion commUnion;

                int bytes_read = net_driver.read_packet (&commUnion, sizeof (commUnion));

				switch (commUnion.type) {
					case (uint32_t)CommandType::LED_COMMAND:
						printf ("led command\n");
						printf("Red: %u\n", commUnion.led.r);
						printf("Green: %u\n", commUnion.led.g);
						printf("Blue: %u\n", commUnion.led.b);
						break;
					default:
						printf ("unknown command: %i\n", commUnion.type);
						break;
				}

                //char type_buffer[4];

                //memcpy(&type_buffer, &buffer , 4*sizeof(int));

                // uint32_t type = (uint32_t)buffer[0] << 24 |
                //                 (uint32_t)buffer[1] << 16 |
                //                 (uint32_t)buffer[2] << 8 | 
                //                 (uint32_t)buffer[3];

                // memcpy(buffer, type_buffer, 4*sizeof(int));


                //LedCommand led;

				/*
                printf("*****************************\n");
                printf("%d\n", atoi(type_buffer));
                printf("%d\n", led.type);
                printf("*****************************\n");
                if (atoi(type_buffer) == (uint32_t)CommandType::LED_COMMAND) {
                    printf("worked");
                } else {
                    printf("jose is bad");
                }*/
                

                // std::cout << "READ: " << buffer << "\n";
                //printf("READ: %s\n", &buffer[0]);
                
                //LedCommand *led = (LedCommand*)&buffer[0];

                // commUnion = (CommandUnion*)&buffer[0];

                // printf("Red: %u\n", commUnion->led.r);
                // printf("Green: %u\n", commUnion->led.g);
                // printf("Blue: %u\n", commUnion->led.b);

                // printf("Servo Num: %u\n", commUnion->servo.servoNum);
                // printf("Servo Pos: %f\n", commUnion->servo.position);

            }
        } catch (const char* msg) {
            std::cout << "Main: " << msg << std::endl;
        }

        std::cout << "Waiting for heartbeat thread to exit " << std::endl;
        heartbeat.join();

    }

    return 0; 
} 

