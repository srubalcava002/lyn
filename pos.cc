/*
 * this file has definitions for objects that produce information about positioning...
 *
 * 
*/

#include "pos.h"

void log(int level, char* message);

IMU::IMU() {
	qua_z = 0;
	qua_z = 0;
	qua_z = 0;

	gyro_z = 0;
	gyro_z = 0;
	gyro_z = 0;

	mag_z = 0;
	mag_z = 0;
	mag_z = 0;

	acc_z = 0;
	acc_z = 0;
	acc_z = 0;

	temp = 0;
	pitch = 0;
	roll = 0;

	calibration = 0b00000000;

	moving_threshold = 0;

	printf("created new imu object...\ncalibrating...\n");

	while (calibration != 0xff) {
		read_calibration();
	}

	printf("calibrated imu\n");
}

void IMU::read_calibration() {
	calibration = wiringPiI2CReadReg8(ADDR, CAL_REG);
}

void IMU::update_qua() {
	qua_z = wiringPiI2CReadReg16(ADDR, QUA_Z);
	qua_y = wiringPiI2CReadReg16(ADDR, QUA_Y);
	qua_x = wiringPiI2CReadReg16(ADDR, QUA_X);
}

void IMU::update_gyro() {
	gyro_z = wiringPiI2CReadReg16(ADDR, GYRO_Z);
	gyro_y = wiringPiI2CReadReg16(ADDR, GYRO_Y);
	gyro_x = wiringPiI2CReadReg16(ADDR, GYRO_X);
}

void IMU::update_mag() {
	mag_z = wiringPiI2CReadReg16(ADDR, MAG_Z);
	mag_y = wiringPiI2CReadReg16(ADDR, MAG_Y);
	mag_x = wiringPiI2CReadReg16(ADDR, MAG_X);
}

void IMU::update_acc() {
	acc_z = wiringPiI2CReadReg16(ADDR, ACC_Z);
	acc_y = wiringPiI2CReadReg16(ADDR, ACC_Y);
	acc_x = wiringPiI2CReadReg16(ADDR, ACC_X);
}

void IMU::update_temp() {
	temp = wiringPiI2CReadReg16(ADDR, TEMP);
}

void IMU::update_pitch() {
	pitch = wiringPiI2CReadReg16(ADDR, PITCH);
}

void IMU::update_roll() {
	roll = wiringPiI2CReadReg16(ADDR, ROLL);
}

void IMU::update_all() {
	if (calibration == 0xff) {
		update_qua();
		update_gyro();
		update_mag();
		update_acc();
		update_temp();
		update_pitch();
		update_roll();

		// threshold needs tuning
		if (acc_x + acc_y + acc_z > moving_threshold) {
			moving = true;
		}
		else {
			moving = false;
		}
	}
	else {
		log(2, "IMU not fully calibrated");
		printf("IMU not fully calibrated: %d\n", calibration);
	}

	read_calibration();
}

PLATE::PLATE() {
	log(1, "creating lyn <-> python unix socket...\n");
	// init socket for communication with tetra here
	socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);

	memset(&addr, 0, sizeof(struct sockaddr_un));

	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path) - 1);

	if (socket_fd == -1) {
		log(2, "problem creating tetra socket...");
	}
	log(0, "created tetra socket");

	if (bind(socket_fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1) {
		log(2, "problem binding socket...");
	}
	log(0, "socket bound");

	if (listen(socket_fd, 50) == -1) {
		log(2, "problem with listen() call...");
	}
	log(0, "marked socket to listen");

	socklen_t size = sizeof(addr);
	if (accept(socket_fd, (struct sockaddr *) &addr, &size) == -1) {
		log(2, "problem with accepting connections...");
	}
	log(0, "accepting connections");

	// start the python script here
	log(1, "starting python script...");

	// can pass args to the camera here
	// maybe have a default exposure setting if
	// not using args here
	char** camargs = {NULL};
	char** camenv = {NULL};
	execve("/home/user/lyn/cam.py", camargs, camenv);
}

void IMU::update_loop() {
	log(1, "started imu update loop");
	while (true) {
		update_all();
	}
}

void PLATE::update_loop(struct position_resolution* prs) {
	log(1, "started plate solver update loop\n");
	while (true) {
		if (prs->imu->moving) {
			continue;
		}
	}
}

void start_orientation_thread(struct position_resolution* prs) {
	// start the threads for the solver and imu
	std::thread imu_thread(&IMU::update_loop, std::ref(prs->imu));
	std::thread plate_thread(&PLATE::update_loop, std::ref(prs->plate), std::ref(prs));
	// main loop here
	while (true) {
		if (prs->imu->moving) {
			log(0, "using imu data");
			prs->alt = prs->imu->alt;
			prs->az = prs->imu->az;
		}
		else {
			log(0, "using plate solve data");
			prs->alt = prs->plate->alt;
			prs->az = prs->plate->az;
		}
	}
}

void log(int level, char* message) {
	switch (level) {
		case 0:
			printf("[DEBUG]\t");
			break;
		case 1:
			printf("[INFO]\t");
			break;
		case 2:
			printf("[ERROR]\t");
			break;
		default:
			break;
	}
	printf("%s\n", message);
}

