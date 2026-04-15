#include <Arduino.h>
#include <math.h>
#include "leveling.h"
#include "imu.h"

static float roll_deg = 0.0f;
static float pitch_deg = 0.0f;

static const float level_tolerance_deg = 0.5f;

void leveling_init() {
    roll_deg=0.0f;
    pitch_deg = 0.0f;

}

void leveling_update() {
    float ax = imu_get_accel_x();
    float ay = imu_get_accel_y();
    float az = imu_get_accel_z();

    // Basic tilt calculation from accelerometer
    float roll_rad = atan2(ay, az);
    float pitch_rad = atan2(-ax, sqrt((ay * ay) + (az * az)));

    roll_deg = roll_rad * 100.0f/PI;
    pitch_deg = pitch_rad * 100.0f/PI;

}

float leveling_get_roll_deg() {
    return roll_deg;
}

float leveling_get_pitch_deg() {
    return pitch_deg;
}

const char* leveling_get_roll_status() {
    if ( roll_deg > level_tolerance_deg) {
        return "Right side low";
    }
    if (roll_deg < -level_tolerance_deg) {
        return "Left side low";
    }
    return "Side-to-side level";
}

const char* leveling_get_pitch_status() {
    if (pitch_deg > level_tolerance_deg) {
        return "Front high";
    }
    if (pitch_deg < -level_tolerance_deg) {
        return "Front low";
    }
    return "Front-to-back level";
}
bool leveling_is_level() {
    return (fabs(roll_deg) <= level_tolerance_deg) && (fabs(pitch_deg) <= level_tolerance_deg);
    
}