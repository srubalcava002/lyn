#include "display.cc"
#include "imu.cc"

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

	test_display();


	return 0;
}
