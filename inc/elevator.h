#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <stdbool.h>

#define NUMBER_OF_ELEVATORS 16
#define NUMBER_OF_FLOORS 20

void elevator_init(void);

void elevator_call(int user_floor, int direction);

bool elevator_ride(int elev_index, int target_floor);

void elevator_step(void);

bool elevator_floor_reached_check(int elev_index);

bool elevator_on_floor_check(int floor);

#endif /* ELEVATOR_H */