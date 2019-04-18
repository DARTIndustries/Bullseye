// Client side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <string.h>
#include <iostream>

#include <commands/ServoCommand.h>
#include <commands/LedCommand.h>
#include <commands/CommandUnion.h>


#define PORT 8000
   
int main() 
{ 
    struct sockaddr_in address; 
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    //char* hello = "Hello from client"; 
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        std::cout << "Socket creation error" << std::endl; 
        return -1; 
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        std::cout << "Invalid address/ Address not supported " << std::endl; 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        std::cout << "Connection Failed" << std::endl; 
        return -1; 
    } 

    CommandUnion commUnion;

    LedCommand led;
    led.b = 0;
    led.r = 4;
    led.g = 2;

    // ServoCommand servo;
    // servo.position = 20;
    // servo.servoNum = 1;

    commUnion.type = (uint32_t)CommandType::LED_COMMAND;
    printf("%d\n",commUnion.type);
    commUnion.led = led;
    // commUnion.servo = servo;

    //send(sock , hello , strlen(hello) , 0 ); 
    send(sock, &commUnion, sizeof(commUnion), 0);
    send(sock, &commUnion, sizeof(commUnion), 0);
    send(sock, &commUnion, sizeof(commUnion), 0);
    // std::cout << "Hello message sent\n" << std::endl;
    
    while(read( sock , buffer, sizeof(buffer)) != -1){
      send(sock, &commUnion, sizeof(commUnion), 0);
      LedCommand *led = (LedCommand*)&buffer[0];

      printf("Red: %u\n", led->r);
      printf("Green: %u\n", led->g);
      printf("Blue: %u\n", led->b);
    }

    return 0; 
} 