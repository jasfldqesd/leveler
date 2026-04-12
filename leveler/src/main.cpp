#include "imu.h"
#include "leveling.h"
#include "web.h"
#include <Arduino.h>

void setup(){
    Serial.begin(115200);

    imu_init();
    leveling_init();
    web_init();
}
void loop(){
    imu_update();
    leveling_update();
    web_update();
}
