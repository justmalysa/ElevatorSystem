#include <elevator.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct elevator_status
{
    int current_floor;
    int target_floor;
    bool is_busy;
};

struct elevator_status elevator_tab[NUMBER_OF_ELEVATORS];

void elevator_init(void)
{
    memset(elevator_tab, 0, sizeof(elevator_tab));
}

int elevator_call(int user_floor, int direction)
{
    int min_difference = NUMBER_OF_FLOORS + 1;
    int elev_index = 0;

    for (size_t i = 0; i < NUMBER_OF_ELEVATORS; i++)
    {
        int difference = abs(elevator_tab[i].current_floor - user_floor);
        if ((difference < min_difference) && !(elevator_tab[i].is_busy))
        {
            min_difference = difference;
            elev_index = i;
        }
    }

    if (min_difference < NUMBER_OF_FLOORS + 1)
    {
        elevator_tab[elev_index].target_floor = user_floor;
    }
    return elev_index;
}

void elevator_ride(int elev_index, int target_floor)
{
    elevator_tab[elev_index].target_floor = target_floor;
}

void elevator_step(void)
{
    for (size_t i = 0; i<NUMBER_OF_ELEVATORS; i++)
    {
        struct elevator_status * p_elev = &elevator_tab[i];
        if (p_elev->current_floor > p_elev->target_floor)
        {
            p_elev->current_floor--;
        }
        else if (p_elev->current_floor < p_elev->target_floor)
        {
            p_elev->current_floor++;
        }

        if(p_elev->current_floor == p_elev->target_floor)
        {
            p_elev->is_busy = false;
        }
    }
}

bool elevator_floor_reached_check(int elev_index)
{
    struct elevator_status * p_elev = &elevator_tab[elev_index];
    return (p_elev->current_floor == p_elev->target_floor);
}
