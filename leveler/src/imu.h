#ifndef IMU_H
#define IMU_H

void imu_init();
void imu_update();

float imu_get_accel_x();
float imu_get_accel_y();
float imu_get_accel_z();

#endif