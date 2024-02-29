#include "pos.cc"
#define BCM2835_NO_DELAY_COMPATIBILITY
#include "display.cc"
#include <stdio.h>
#include <thread>

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

double current_ra = 0;
double current_dec = 0;

int main(int argc, char** argv) {
	// maybe have the main display loop init the display
	if (!init_display()) {
		printf("problem initializing display!\n");
		return -1;
	}
	else {
		printf("display initialized\n");
	}

	// needs to be refactored create the new object thing
	plate_fake *plate = new plate_fake();

	// create thread to handle display
	std::thread display_thread(start_display_loop, plate);

	// create thread to handle orientation
	// read up on calling member functions as thread
	//std::thread orientation_thread(generate_test_data, plate);

	return 0;
}

