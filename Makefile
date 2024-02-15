all:
	g++ -g -Wall lyn.cc -std=c++11 -lbcm2835 -lrt -lSSD1306_OLED_RPI -lwiringPi -o lyn
