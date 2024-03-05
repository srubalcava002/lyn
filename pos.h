/*
 * this file has definitions for objects that produce information about positioning...
 *
 * 
*/
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <cstdint>
#include <stdio.h>

#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <string.h>

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

class IMU {
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

		uint16_t moving_threshold;

		bool moving = false;

		void read_calibration();
		void update_qua();
		void update_gyro();
		void update_mag();
		void update_acc();
		void update_temp();
		void update_pitch();
		void update_roll();
		void update_all();
		
		IMU();
};

class imu_fake {
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

		uint16_t alt;
		uint16_t az; 

		uint8_t calibration;

		bool moving;

		/*
		void read_calibration();
		void update_qua();
		void update_gyro();
		void update_mag();
		void update_acc();
		void update_temp();
		void update_pitch();
		void update_roll();
		void update_all();
		*/

		void fake_data();

		imu_fake();


};

// unimplemented
// should interface with the camera and produce an image
// also contains its own local data that should be interpreted as 
// the main reference 
class PLATE {
	public:
		const char* socket_path = "~/lyn/image_q";
		struct sockaddr_un addr;
		int socket_fd;

		PLATE();
};

// unimplemented
// produces fake test data
class plate_fake {
	public:
		imu_fake imu;
		float az;
		float alt;

		void generate_test_data();
		plate_fake();
};

void start_orientation_thread(struct position_resolution* prs);

struct global_data {
	float ra;
	float dec;
	float alt;
	float az;
};

// needs to exist to keep std::thread happy
// only takes one arg
struct position_resolution {
	PLATE* plate;
	IMU* imu;
	global_data* data;
};
