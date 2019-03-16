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

	// Removes the random characters at the end
	memset (buffer, 0, sizeof buffer);

    NetworkingDriver net_driver;
    
	net_driver.open_connection();

    while(true){
        
        //spawn heartbeat thread
        // std::thread heartbeat (heartbeat_thread, net_driver);
        // std::cout << "main, foo and bar now execute concurrently...\n";
        // heartbeat.join();

		int i = net_driver.read_packet (buffer, sizeof (buffer));

		if (i == 0) { // Client disconnected, exit
			std::cout << "Connection closed\n";
			net_driver.close_connection();
			return 0;
		} else { // Message received
			std::cout << "READ: " << buffer << "\n";

			// Clears buffer
			memset(buffer, 0, sizeof buffer);

			char test_response[] = "Response\n";
			net_driver.send_packet (&test_response, sizeof (test_response));
		}

        //example of struct being sent
        /*LedCommand led;

        led.b = 5;
        led.r = 1;
        led.g = 255;

        net_driver.send_packet(&led, sizeof(led));*/
    }
    
    //TODO: Close?

    // send(new_socket , hello , strlen(hello) , 0 ); 
    // printf("Hello message sent\n"); 
    return 0; 
} 

//TODO: Move to driver code


