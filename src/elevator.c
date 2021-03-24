#include <elevator.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DIR_UP   1
#define DIR_DOWN 0

struct elevator_status
{
    int current_floor;
    int target_floor;
    bool requested_floors[NUMBER_OF_FLOORS];
};

struct floor_status
{
    int direction;
    bool is_requested;
};

struct elevator_status elevator_arr[NUMBER_OF_ELEVATORS];
struct floor_status floor_arr[NUMBER_OF_FLOORS];

void elevator_init(void)
{
    memset(elevator_arr, 0, sizeof(elevator_arr));
}

void elevator_call(int user_floor, int direction)
{
    floor_arr[user_floor].is_requested = true;
    floor_arr[user_floor].direction = direction;
}

bool elevator_ride(int user_floor, int target_floor)
{
    for (size_t i = 0; i < NUMBER_OF_ELEVATORS; i++)
    {
        struct elevator_status * p_elev = &elevator_arr[i];
        if ((p_elev->target_floor == user_floor) && (p_elev->current_floor == p_elev->target_floor))
        {
            p_elev->requested_floors[target_floor] = true;
            p_elev->target_floor = target_floor;
            return true;
        }
    }
    return false;
}

void elevator_step(void)
{
    for (size_t floor_idx = 0; floor_idx<NUMBER_OF_FLOORS; floor_idx++)
    {
        struct floor_status * p_floor = &floor_arr[floor_idx];

        if (p_floor->is_requested)
        {
            int min_difference = NUMBER_OF_FLOORS + 1;
            int elev_index = 0;

            for (size_t i = 0; i < NUMBER_OF_ELEVATORS; i++)
            {
                struct elevator_status * p_elev = &elevator_arr[i];
                int difference = abs(p_elev->current_floor - floor_idx);

                bool is_on_the_way_target =
                    (p_elev->target_floor > floor_idx && (p_floor->direction == DIR_UP)) ||
                    (p_elev->target_floor < floor_idx && (p_floor->direction == DIR_DOWN));

                bool is_on_the_way_current =
                    (p_elev->current_floor < floor_idx && (p_floor->direction == DIR_UP)) ||
                    (p_elev->current_floor > floor_idx && (p_floor->direction == DIR_DOWN));

                bool is_idle = (p_elev->target_floor == p_elev->current_floor);

                if ((difference < min_difference) && ((is_on_the_way_current && is_on_the_way_target) || is_idle))
                {
                    min_difference = difference;
                    elev_index = i;
                }
            }

            if (min_difference < NUMBER_OF_FLOORS + 1)
            {
                elevator_arr[elev_index].target_floor = floor_idx;
                elevator_arr[elev_index].requested_floors[floor_idx] = true;
            }
        }
    }

    for (size_t i = 0; i<NUMBER_OF_ELEVATORS; i++)
    {
        struct elevator_status * p_elev = &elevator_arr[i];
        if (p_elev->current_floor > p_elev->target_floor)
        {
            p_elev->current_floor--;
        }
        else if (p_elev->current_floor < p_elev->target_floor)
        {
            p_elev->current_floor++;
        }

        if (p_elev->current_floor == p_elev->target_floor)
        {
            p_elev->requested_floors[p_elev->current_floor] = false;
            if (floor_arr[p_elev->current_floor].is_requested)
            {
                floor_arr[p_elev->current_floor].is_requested = false;
            }
        }
    }
}

bool elevator_floor_reached_check(int elev_index)
{
    struct elevator_status * p_elev = &elevator_arr[elev_index];
    return (p_elev->current_floor == p_elev->target_floor);
}

bool elevator_on_floor_check(int floor)
{
    for (size_t i = 0; i < NUMBER_OF_ELEVATORS; i++)
    {
        struct elevator_status * p_elev = &elevator_arr[i];
        if ((p_elev->target_floor == floor) && (p_elev->current_floor == p_elev->target_floor))
        {
            return true;
        }
    }
    return false;
}