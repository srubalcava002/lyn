/*
 * this file has definitions for objects that produce information about positioning...
 *
 * 
*/

#include "pos.h"

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

	printf("created new imu object...");
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
		printf("IMU not fully calibrated: %d\n", calibration);
	}
}

void imu_fake::fake_data() {

	while (true) {
		for (int i = 0; i < 360; i++) {
			az = i;	
		}
	}

}

imu_fake::imu_fake() {
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

	az = 0;

	moving = false;

	printf("created new fake imu object...");
}

// chooses between imu or plate solver data based on movement
void plate_fake::generate_test_data() {
	while (true) {
		if (imu.moving) {
			// get data from imu
			az = imu.az;
			alt = imu.alt;
		}
		else {
			// get data from plate solver
			// fakes the data here for now
			az++;
			alt++;
		}
	}
}

plate_fake::plate_fake() {
	// unimplemented
	// should probably init imu and plate solver here
}

PLATE::PLATE() {
	// init socket for communication with tetra here
	socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);

	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path));

	if (socket_fd == -1) {
		printf("problem creating tetra socket...\n");
	}
	

	if (bind(socket_fd, (struct sockaddr *) &addr, sizeof(addr) == -1)) {
		printf("problem binding socket...\n");
	}

	if (listen(socket_fd, 50) == -1) {
		printf("problem with listen() call...\n");
	}

	socklen_t size = sizeof(addr);
	if (accept(socket_fd, (struct sockaddr *) &addr, &size) == -1) {
		printf("problem with accepting connections...\n");
	}

	// start the python script here
	
}

void start_orientation_thread(struct position_resolution* prs) {
	// main loop here
	while (true) {
		if (prs->imu->moving) {
			printf("using imu data\n");
		}
		else {
			printf("using plate solve data\n");
		}
	}
}

