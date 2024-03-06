#include "pos.cc"
#define BCM2835_NO_DELAY_COMPATIBILITY
#include "display.cc"
#include <stdio.h>

/*
#include <wiringPi.h>
#define BCM2835_NO_DELAY_COMPATIBILITY
#include <wiringPiI2C.h>

#include <bcm2835.h>
#include <stdio.h>
#include <SSD1306_OLED.hpp>
#include <SSD1306_OLED_Print.hpp>
#include <string>
*/

// lyn needs to run as root!
int main(int argc, char** argv) {
	printf("starting lyn!\n");
	// maybe have the main display loop init the display
	if (!init_display()) {
		printf("problem initializing display!\n");
		return -1;
	}
	else {
		printf("display initialized\n");
	}

	// according to the plan:
	// one thread handles the display
	// one thread handles positioning (with two child threads for imu and plate solver)
	// needs to be refactored create the new object thing
	PLATE *plate_real = new PLATE();
	IMU *imu = new IMU();

	position_resolution* prs = (position_resolution*) malloc(sizeof(position_resolution)); 
	prs->plate = plate_real;
	prs->imu = imu;

	// create thread to handle display
	std::thread display_thread(start_display_loop, prs);

	// create thread to handle orientation
	std::thread orientation_thread(start_orientation_thread, prs);
	
	printf("started all threads\n");

	return 0;
}

