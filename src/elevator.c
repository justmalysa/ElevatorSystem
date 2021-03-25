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
    int last_reached_floor;
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

        int elev_direction = p_elev->target_floor - p_elev->current_floor;

        bool is_on_user_floor = p_elev->current_floor == user_floor;

        bool is_idle = (elev_direction == 0);

        bool is_target_floor_further =
            (p_elev->target_floor < target_floor && (elev_direction > 0)) ||
            (p_elev->target_floor > target_floor && (elev_direction < 0));

        bool is_same_direction = ((target_floor > user_floor) && (elev_direction > 0)) ||
                                 ((target_floor < user_floor) && (elev_direction < 0));

        if (is_on_user_floor && (is_same_direction || is_idle))
        {
            if (is_target_floor_further || is_idle)
            {
                p_elev->target_floor = target_floor;
            }
            p_elev->requested_floors[target_floor] = true;
            floor_arr[user_floor].is_requested = false;
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

                if ((difference < min_difference) &&
                    ((is_on_the_way_current && is_on_the_way_target) || is_idle))
                {
                    min_difference = difference;
                    elev_index = i;
                }
            }

            if (min_difference < NUMBER_OF_FLOORS + 1)
            {
                int elev_direction =
                    elevator_arr[elev_index].target_floor - elevator_arr[elev_index].current_floor;

                bool is_floor_idx_further =
                    ((floor_idx > elevator_arr[elev_index].target_floor) && (elev_direction > 0)) ||
                    ((floor_idx < elevator_arr[elev_index].target_floor) && (elev_direction < 0));

                bool is_idle = (elev_direction == 0);

                if (is_floor_idx_further || is_idle)
                {
                    elevator_arr[elev_index].target_floor = floor_idx;
                }
                elevator_arr[elev_index].requested_floors[floor_idx] = true;
            }
        }
    }

    for (size_t elev_idx = 0; elev_idx < NUMBER_OF_ELEVATORS; elev_idx++)
    {
        struct elevator_status * p_elev = &elevator_arr[elev_idx];
        if (p_elev->current_floor > p_elev->target_floor)
        {
            p_elev->current_floor--;
        }
        else if (p_elev->current_floor < p_elev->target_floor)
        {
            p_elev->current_floor++;
        }

        if (p_elev->requested_floors[p_elev->current_floor])
        {
            p_elev->requested_floors[p_elev->current_floor] = false;
            p_elev->last_reached_floor = p_elev->current_floor;
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
        if ((p_elev->last_reached_floor == floor) && (p_elev->current_floor == floor))
        {
            return true;
        }
    }
    return false;
}