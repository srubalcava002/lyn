#include <wiringPi.h>
#include <wiringPiI2C.h>

#define ADDR 0xff

#define TEMP 0x34

#define QUA_Z 0x27
#define QUA_Y 0x25
#define QUA_X 0x23

#define PITCH 0x1f

#define ROLL 0x1d

#define GYRO_Z 0x19
#define GYRO_Y 0x17
#define GYRO_X 0x16

#define MAG_Z 0x13
#define MAG_Y 0x11
#define MAG_X 0x0f

#define ACC_Z 0x0d
#define ACC_Y 0x0b
#define ACC_X 0x09

#define CAL_REG 0x35

class imu {
	public:
		uint16_t qua_z;
		uint16_t qua_y;
		uint16_t qua_x;

		uint16_t gyro_z;
		uint16_t gyro_y;
		uint16_t gyro_x;

		uint16_t mag_z;
		uint16_t mag_y;
		uint16_t mag_x;

		uint16_t acc_z;
		uint16_t acc_y;
		uint16_t acc_x;

		uint16_t temp;
		uint16_t pitch;
		uint16_t roll;

		uint8_t calibration;

		void read_calibration();
		void update_qua();
		void update_gyro();
		void update_mag();
		void update_acc();
		void update_temp();
		void update_pitch();
		void update_roll();
		void update_all();
		
};

void imu::read_calibration() {
	calibration = wiringPiI2CReadReg8(ADDR, CAL_REG);
}

void imu::update_qua() {
	qua_z = wiringPiI2CReadReg16(ADDR, QUA_Z);
	qua_y = wiringPiI2CReadReg16(ADDR, QUA_Y);
	qua_x = wiringPiI2CReadReg16(ADDR, QUA_X);
}

void imu::update_gyro() {
	gyro_z = wiringPiI2CReadReg16(ADDR, GYRO_Z);
	gyro_y = wiringPiI2CReadReg16(ADDR, GYRO_Y);
	gyro_x = wiringPiI2CReadReg16(ADDR, GYRO_X);
}

void imu::update_mag() {
	mag_z = wiringPiI2CReadReg16(ADDR, MAG_Z);
	mag_y = wiringPiI2CReadReg16(ADDR, MAG_Y);
	mag_x = wiringPiI2CReadReg16(ADDR, MAG_X);
}

void imu::update_acc() {
	acc_z = wiringPiI2CReadReg16(ADDR, ACC_Z);
	acc_y = wiringPiI2CReadReg16(ADDR, ACC_Y);
	acc_x = wiringPiI2CReadReg16(ADDR, ACC_X);
}

void imu::update_temp() {
	temp = wiringPiI2CReadReg16(ADDR, TEMP);
}

void imu::update_pitch() {
	pitch = wiringPiI2CReadReg16(ADDR, PITCH);
}

void imu::update_roll() {
	roll = wiringPiI2CReadReg16(ADDR, ROLL);
}

void imu::update_all() {
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
		printf("imu not fully calibrated: %d\n", calibration);
	}
}
