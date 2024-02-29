#include <bcm2835.h>
#include <stdio.h>
#include <SSD1306_OLED.hpp>
#include <SSD1306_OLED_Print.hpp>
#include <string>
#include <unistd.h>

#define CALIBRATION_X 0
#define CALIBRATION_Y -5

uint16_t speed = 626;
uint8_t display_address = 0x3c;
SSD1306 display = SSD1306(128, 64);

bool buffer_flag = false;
uint8_t buffer[(128 * (64/8)) + 1];
uint8_t buffer2[(128 * (64/8)) + 1];

void draw_reticle(int offset_x, int offset_y);
void update_heading(int alt, int az);
void test_display();
void draw_frame();
void update_buffers();

void update_heading(int alt, int az) {
	// clear old values
	display.fillRect(0, 10, 128, 10, BLACK);

	display.setCursor(35, 10);
	display.print(az);

	display.setCursor(80, 10);
	display.print(alt);
	
	display.OLEDupdate();
}

void draw_reticle(int offset_x, int offset_y) {
	int x = 64 + offset_x;
	int y = 32 + offset_y;

	display.drawTriangle(x-3, y+2, x+3, y+2, x, y-5, WHITE);
	display.OLEDupdate();
}

bool init_display() {
	if (!bcm2835_init()) {
		printf("bcm library could not initialize\n");
		return false;
	}
	
	// init display
	bcm2835_delay(500);
	display.OLEDbegin(speed, display_address);
	bcm2835_delay(1000);

	// create display buffer
	//display.OLEDbuffer = (uint8_t*) &buffer;
	display.OLEDSetBufferPtr(128, 64, buffer, sizeof(buffer));

	// configure display text
	display.setTextWrap(false);
	display.setFontNum(OLEDFont_Tiny);
	display.setTextColor(WHITE);
	display.setTextSize(1);

	// clear display buffer
	display.OLEDclearBuffer();

	// draw reticle and basic hud
	display.setCursor(35, 0);
	display.print("AZ");
	display.setCursor(80, 0);
	display.print("ALT");

	draw_reticle(CALIBRATION_X, CALIBRATION_Y);
	
	return true;
}

// call after initializing display
void test_display() {
	printf("starting display test...\n");

	// test pattern
	for (int i = 0; i < 360; i++) {
		update_heading(i, i);
		printf("iterating: %d\n", i);
	}

	// turn off display for testing
	display.OLEDPowerDown();
	bcm2835_close();

	printf("finished test\n");
}

void draw_frame() {
	if (buffer_flag) {
		display.OLEDSetBufferPtr(128, 64, buffer, sizeof(buffer2));
	}
	else {
		display.OLEDSetBufferPtr(128, 64, buffer2, sizeof(buffer));
	}

	buffer_flag = !(buffer_flag);

	display.OLEDupdate();
}

// here is where the map is updated
void update_display() {
	uint8_t *current_buff;

	if (buffer_flag) {
		current_buff = buffer2;
	}
	else {
		current_buff = buffer;
	}


	display.drawRect(0, 15, 128, 15, BLACK);

	// draw_reticle() updates the display
	// might need to be changed...
	draw_reticle(CALIBRATION_X, CALIBRATION_Y);

}

// so what needs to happen here:
// spawns a child process in which
// the imu is read and heading is updated
// i guess the map also needs to be updated
//
// call the this from thread in main!
void start_display_loop(plate_fake *plate) {
	pid_t display_pid = fork();

	if (display_pid == -1) {
		printf("PROBLEM STARTING DISPLAY LOOP\n");
		return;
	}
	else if (display_pid > 0) {
		while (true) {
			update_heading(0, plate->imu.az);
		}
	}
	else {
		printf("STARTED DISPLAY LOOP\n");
	}
}

