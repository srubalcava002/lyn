#include <stdio.h>

int main(int argc, char** argv) {

	char line_buffer[255];

	FILE* fd = fopen("messier", "r");
	if (!fd) {
		printf("ERROR OPENING CATALOG! EXITING...\n");
		return 1;
	}



	return 0;
}
