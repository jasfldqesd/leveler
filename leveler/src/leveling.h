#ifndef LEVELING_H
#define LEVELING_H

void leveling_init();
void leveling_update();

float leveling_get_roll_deg();
float leveling_get_pitch_deg();

const char* leveling_get_status();
const char* leveling_get_pitch_status();

bool leveling_is_level();

#endif