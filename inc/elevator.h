#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <stdbool.h>

#define NUMBER_OF_ELEVATORS  16
#define NUMBER_OF_FLOORS     20
#define DIR_UP                1
#define DIR_DOWN              0

int get_elevator_current_floor(int floor_number);

int get_elevator_target_floor(int floor_number);

void elevator_init(void);

void elevator_call(int user_floor, int direction);

bool elevator_ride(int elev_index, int target_floor);

void elevator_step(void);

bool elevator_floor_reached_check(int elev_index);

bool elevator_on_floor_check(int floor);

#endif /* ELEVATOR_H */