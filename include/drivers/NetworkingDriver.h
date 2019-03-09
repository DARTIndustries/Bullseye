//Networking Driver
//3/2/2019
//DART
//author: Adam (everyone)
#pragma once
#include <stdlib.h>

#define PORT 8000 

class NetworkingDriver {
private:
	int _socket = -1;
public:
	void open_connection();
	void close_connection();
	int read_packet(void* buf, size_t buf_size);
	void send_packet(void* buf, size_t buf_size);
};

