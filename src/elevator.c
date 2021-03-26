#include <elevator.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/** @brief Structure describing elevator status. */
struct elevator_status
{
    ES_INT current_floor;                    /**< Floor that the elevator is currently on. */
    ES_INT target_floor;                     /**< Last floor that the elevator goes to. */
    ES_INT last_reached_floor;               /**< Last floor that the elevator stopped on. */
    bool requested_floors[NUMBER_OF_FLOORS]; /**< Array of floors that were requested to stop on. */
};

/** @brief Structure describing floor status. */
struct floor_status
{
    ES_INT direction;          /**< Direction of the elevator call. Can be @ref DIR_UP or @ref DIR_DOWN. */
    bool is_requested;         /**< True if there was a elevator call on this floor. */
    bool is_assigned_elevator; /**< True if any elevator was assigned to handle this floor call. */
};

struct elevator_status elevator_arr[NUMBER_OF_ELEVATORS];
struct floor_status floor_arr[NUMBER_OF_FLOORS];

ES_INT get_elevator_current_floor(ES_INT elev_index)
{
    return elevator_arr[elev_index].current_floor;
}

ES_INT get_elevator_target_floor(ES_INT elev_index)
{
    return elevator_arr[elev_index].target_floor;
}

void elevator_init(void)
{
    memset(elevator_arr, 0, sizeof(elevator_arr));
}

void elevator_call(ES_INT user_floor, ES_INT direction)
{
    floor_arr[user_floor].is_requested = true;
    floor_arr[user_floor].is_assigned_elevator = false;
    floor_arr[user_floor].direction = direction;
}

bool elevator_ride(ES_INT user_floor, ES_INT target_floor)
{
    /* Look for an elevator that:
       - is on the same floor as the user,
       - goes to the same direction as the user or is idle.
       If such elevator is found, update elevator target floor
       in case user floor is futher than current target floor. */
    for (ES_SIZE_T i = 0; i < NUMBER_OF_ELEVATORS; i++)
    {
        struct elevator_status * p_elev = &elevator_arr[i];

        ES_INT elev_direction = p_elev->target_floor - p_elev->current_floor;

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
    /* For each requested and not handled floor find an elevator to handle the floor call. */
    for (ES_SIZE_T floor_idx = 0; floor_idx<NUMBER_OF_FLOORS; floor_idx++)
    {
        struct floor_status * p_floor = &floor_arr[floor_idx];

        if (p_floor->is_requested && !(p_floor->is_assigned_elevator))
        {
            ES_INT min_difference = NUMBER_OF_FLOORS + 1;
            ES_INT elev_index = 0;

            /* Look for an elevator that is closest to called floor.
               Elevator can either go in the same direction as the user or be idle. */
            for (ES_SIZE_T i = 0; i < NUMBER_OF_ELEVATORS; i++)
            {
                struct elevator_status * p_elev = &elevator_arr[i];
                ES_INT difference = abs(p_elev->current_floor - floor_idx);

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

            /* If suitable elevator is found, check whether target floor needs to be updated. */
            if (min_difference < NUMBER_OF_FLOORS + 1)
            {
                ES_INT elev_direction =
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
                floor_arr[elevator_arr[elev_index].target_floor].is_assigned_elevator = true;
            }
        }
    }

    /* After processing all of the elevator calls, advance the simulation by one step.
       One simulation step equals to move by one floor of each of the elevators. */
    for (ES_SIZE_T elev_idx = 0; elev_idx < NUMBER_OF_ELEVATORS; elev_idx++)
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

        /* If a floor that was reqested for this particular elevator is reached, mark it as reached. */
        if (p_elev->requested_floors[p_elev->current_floor])
        {
            p_elev->requested_floors[p_elev->current_floor] = false;
            p_elev->last_reached_floor = p_elev->current_floor;
        }
    }
}

bool elevator_on_floor_check(ES_INT floor)
{
    /* Look for an elevator that:
       - is on the same floor as the provided floor,
       - was recently reached by given elevator. */
    for (ES_SIZE_T i = 0; i < NUMBER_OF_ELEVATORS; i++)
    {
        struct elevator_status * p_elev = &elevator_arr[i];
        if ((p_elev->last_reached_floor == floor) && (p_elev->current_floor == floor))
        {
            return true;
        }
    }
    return false;
}