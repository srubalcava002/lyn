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

int main(int argc, char** argv) {
	if (!bcm2835_init()) {
		printf("bcm library could not initialize\n");
		return 1;
	}

	bcm2835_delay(500);
	display.OLEDbegin(speed, display_address);
	bcm2835_delay(1000);

	uint8_t buffer[(128 * (64/8)) + 1];
	display.buffer = (uint8_t*) &buffer;

	display.setTextWrap(false);
	display.setFontNum(OLEDFontType_Tiny);

	display.OLEDclearBuffer();

	display.setTextColor(WHITE);
	display.setTextSize(1);

	display.setCursor(35, 0);
	display.print("AZ");
	display.setCursor(80, 0);
	display.print("ALT");

	draw_reticle(0, -5);
	
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 360; i++) {
			update_heading(i, i);
			printf("iterating: %d\n", i);
		}
	}

	display.OLEDPowerDown();
	bcm2835_close();
	printf("finished test\n");
	
	return 0;
}

