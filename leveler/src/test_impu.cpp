#include <Arduino.h>
#include "test_impu.h"

static float accel_x = 0.0f;
static float accel_y = 0.0f;
static float accel_z = 0.0f;

static float t = 0.0f;

void sim_init(){
    Serial.println("IMU Simulation Initialized");

}

void sim_update() {
    //simulate slow tilt motion
    t += 0.05f;

    accel_x = 9.8f * sin(t);
    accel_y = 0.0f;
    accel_z = 9.8f * cos(t);
}

float sim_get_accel_x() {return accel_x;}
float sim_get_accel_y() {return accel_y;}
float sim_get_accel_z() {return accel_z;}
