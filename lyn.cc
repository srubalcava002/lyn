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

double current_ra = 0;
double current_dec = 0;

int main(int argc, char** argv) {
	if (!init_display()) {
		printf("problem initializing display!\n");
		return -1;
	}
	else {
		printf("display initialized\n");
	}

	imu_fake *imu = new imu_fake();

	test_display();

	return 0;
}


