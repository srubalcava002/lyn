#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <cstdint>
#include <stdio.h>
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

	printf("created new fake imu object...");
}
