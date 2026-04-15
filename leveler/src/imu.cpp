#include <Arduino.h>
#include "imu.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

static Adafruit_MPU6050 mpu;

static float accel_x = 0.0f;
static float accel_y = 0.0f;
static float accel_z = 0.0f;



void imu_init() {
    if (!mpu.begin()) {
        Serial.println("Failed to find MPU6050");
        while (true) {
            delay(1000);
        }
    }
    Serial.println("MPU6050 Initialized");

    //optional tuning
    mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
    mpu.setGyroRange(MPU6050_RANGE_250_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

    delay(100);

}

void imu_update() {
    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t temp;

    mpu.getEvent(&accel, &gyro, &temp);

    accel_x = accel.acceleration.x;
    accel_y = accel.acceleration.y;
    accel_z = accel.acceleration.z;
}
float imu_get_accel_x() {
    return accel_x;
}
float imu_get_accel_y() {
    return accel_y;
}
float imu_get_accel_z() {
    return accel_z;
}


