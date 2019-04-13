#include <iostream>
#include <drivers/AbstractPwmDriver.h>
#include <drivers/Adafruit16ChPwmHatDriver.h>
#include <commands/ServoCommand.h>
#include <controllers/ServoController.h>
#include <drivers/NetworkingDriver.h>
#include <commands/CommandUnion.h>
#include <controllers/LedController.h>
#include <thread>
#include <unistd.h>

void heartbeat_thread (NetworkingDriver net_driver) {
	std::cout << "Heartbeat thread started up " << std::endl;
	try {
		while (true) {

			LedCommand led;
			led.b = 5;
			led.r = 1;
			led.g = 255;

			// char* testMsg = "Hello World";

			net_driver.send_packet (&led, sizeof (led));
			// net_driver.send_packet(&testMsg, sizeof(testMsg));
			sleep (1);
		}
	}
	catch (const char* msg) {
		std::cout << "Heartbeat thread: " << msg << std::endl;
	}
	std::cout << "Heartbeat exiting " << std::endl;
}

int main() {
	/*
    std::cout << "WE ARE DART!" << std::endl;
    std::cout << "AND WE HAVE CI" << std::endl;
    std::cout << "AND WE HAVE BULLSEYE!" << std::endl;

	auto pwmDriver = Adafruit16ChPwmHatDriver(1, 0x40);

	pwmDriver.setFrequency(60);
	pwmDriver.setDutyCycle(12, 0.5);
	*/

	//Testing servo controller
	/*
	auto pwmDriver = Adafruit16ChPwmHatDriver(1, 0x40);
	ServoCommand com; 
	com.position = 0.5;

	servo.execute(&com);
	*/

	auto pwmDriver = Adafruit16ChPwmHatDriver (1, 0x40);
	auto ledController = LedController (&pwmDriver);
	auto clawServoController = ServoController (&pwmDriver, 0.1, 0.2, 0.3);

	NetworkingDriver net_driver;

	//Accept loop
	while (true) {

		std::cout << "Listening on localhost:8000 " << std::endl;
		net_driver.open_connection ();
		std::cout << "Client Connected " << std::endl;

		std::thread heartbeat (heartbeat_thread, net_driver);

		try {
			//Receive messages loop
			while (true) {

				CommandUnion commUnion;

				int bytes_read = net_driver.read_packet (&commUnion, sizeof (commUnion));

				switch (commUnion.type) {
					case (uint32_t)CommandType::LED_COMMAND:
						printf ("led command\n");
						printf ("Red: %u\n", commUnion.led.r);
						printf ("Green: %u\n", commUnion.led.g);
						printf ("Blue: %u\n", commUnion.led.b);

						ledController.execute(&commUnion.led);

						break;
					case (uint32_t)CommandType::SERVO_COMMAND:
						clawServoController.execute (&commUnion.servo);
						break;
					default:
						printf ("unknown command: %i\n", commUnion.type);
						break;
				}
			}
		}
		catch (const char* msg) {
			std::cout << "Main: " << msg << std::endl;
		}

		std::cout << "Waiting for heartbeat thread to exit " << std::endl;
		heartbeat.join ();
	}

    return 0;
}


