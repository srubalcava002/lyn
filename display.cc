#include <bcm2835.h>
#include <stdio.h>
#include <SSD1306_OLED.hpp>
#include <SSD1306_OLED_Print.hpp>
#include <string>

uint16_t speed = 626;
uint8_t display_address = 0x3c;
SSD1306 display = SSD1306(128, 64);


void draw_reticle(int offset_x, int offset_y);
void update_heading(int alt, int az);

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
	uint8_t buffer[(128 * (64/8)) + 1];
	display.buffer = (uint8_t*) &buffer;

	// configure display text
	display.setTextWrap(false);
	display.setFontNum(OLEDFontType_Tiny);
	display.setTextColor(WHITE);
	display.setTextSize(1);

	// clear display buffer
	display.OLEDclearBuffer();

	// draw reticle and basic hud
	display.setCursor(35, 0);
	display.print("AZ");
	display.setCursor(80, 0);
	display.print("ALT");

	draw_reticle(0, -5);
	
	// test pattern

	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 360; i++) {
			update_heading(0, 0);
			printf("iterating: %d\n", i);
		}
	}

	// turn off display for testing
	display.OLEDPowerDown();
	bcm2835_close();

	printf("finished test\n");
	
	return true;
}

