#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <drivers/NetworkingDriver.h>
#include <commands/ServoCommand.h>
#include <commands/LedCommand.h>
#include <commands/CommandUnion.h>
#include <exception>
#include <iostream>


/**
 * Reads on the opened socket into an internal buffer. 
 * Returns a pointer to the internal buffer of the command union. 
 * This memory should not be freed.
 * Not re-enterent, not thread safe. 
 */
CommandUnion* NetworkingDriver::read_command() {
    static char buf[1024]; 
    static bool has_data = false;
    static int bytes_used = 0;
    static int bytes_read = 0;
    if (_socket == -1) {
        throw "No Connection";
    }

    /* Read until it returns valid data */
    while(true) {
        /* If the buffer is empty get more data */
        if (!has_data) {
            int leftovers = 0;
            /* If there is data left in the buffer, copy it to the front. Should only be a few bytes */
            if (bytes_used < bytes_read) {
                leftovers = bytes_read - bytes_used;
                memcpy(buf, buf + bytes_used, leftovers);
            }
            bytes_read = read(_socket, buf + leftovers, sizeof(buf) - leftovers); 

            if (bytes_read == 0 || bytes_read == -1) {
                    throw "Client disconnect";
            }
            bytes_read += leftovers; // Add leftovers at the front to the size
            bytes_used = 0;
            has_data = true;
        }

        if (bytes_read < 4) {
            has_data = false;
            continue;
        }
        
        /* Switch to check size */
        CommandUnion *comm = (CommandUnion*)buf + bytes_used;
        size_t com_size = 0;
        switch (comm->type) {
            case (uint32_t)CommandType::LED_COMMAND: com_size = sizeof(LedCommand); break;
            case (uint32_t)CommandType::SERVO_COMMAND: com_size = sizeof(ServoCommand); break;
            default: 
                printf("Unknown Command Size!!!! Unrecoverable Error");
                throw "Unknown Command Size";
        }

        if (bytes_read - bytes_used < sizeof(com_size)) {
            has_data = false;
            continue;
        }
        bytes_used += com_size;
        return comm;
    }
}



/**
 * Reads on the opened socket into buf up to buf_size bytes. Throws an exception if socket is not opened
 */
int NetworkingDriver::read_packet(void* buf, size_t buf_size) {
    if (_socket == -1) {
        throw "No Connection";
    }

    int bytes_read = read(_socket, buf, buf_size); 
    
    if( bytes_read == 0 || bytes_read == -1){
        throw "Client disconnect";
    }else{
        return bytes_read;
    }
    
}


int NetworkingDriver::send_packet(void* buf, size_t buf_size) {
    if (_socket == -1) {
        throw "No Connection";
    }
    
    int bytes_send = send(_socket, buf, buf_size, 0);

    if( bytes_send == 0 || bytes_send == -1){
        throw "Client disconnect";
    }else{
        return bytes_send;
    }
}

//TODO: Replace exits with throws to an exception
//TODO: Close server fd?
/** Opens a socket and calls accept on port
 * Once a connection is made it returns a socket
 * Blocking call
 */
void NetworkingDriver::open_connection() {
    int server_fd; 
    struct sockaddr_in address; 
    int addrlen = sizeof(address); 
    int opt = 1; 

    // Creating socket file descriptor

	// (domain, type, proto)
	// use SOCK_DGRAM instead? use '<' instead of '=='?
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = htonl(INADDR_ANY); 
    address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 

    if (listen(server_fd, 3) < 0)  { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    if ((_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    }
    // else{
    //     printf("Server connected\n");
    // }
}

/** Closes socket
 * 
 */
void NetworkingDriver::close_connection(){
    close(_socket);
}
