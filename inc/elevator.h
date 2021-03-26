#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <stdbool.h>
#include <elevator_config.h>

/** @brief Symbol specifying up direction in @ref elevator_call() function. */
#define DIR_UP                1

/** @brief Symbol specifying down direction in @ref elevator_call() function. */
#define DIR_DOWN              0


/**
 * @brief Function for getting current floor of the specified elevator.
 *
 * @param elev_index Index of the elevator to be checked.
 *
 * @return Elevator current floor.
 */
ES_INT get_elevator_current_floor(ES_INT elev_index);

/**
 * @brief Function for getting target floor of the specified elevator.
 *
 * @param elev_index Index of the elevator to be checked.
 *
 * @return Elevator target floor.
 */
ES_INT get_elevator_target_floor(ES_INT elev_index);

/** @brief Function for initializing elevator system. */
void elevator_init(void);

/**
 * @brief Function for calling the elevator to the specified floor.
 *
 * @param user_floor Floor to which elevator is called.
 * @param direction  Direction of the elevator call.
 *                   Can be @ref DIR_UP or @ref DIR_DOWN.
 */
void elevator_call(ES_INT user_floor, ES_INT direction);

/**
 * @brief Function for entering the elevator and choosing a desired floor.
 *
 * @param user_floor   Floor on which user is entering the elevator.
 * @param target_floor User desired floor.
 *
 * @retval true  Operation was successful.
 * @retval false There isn't any elevator on the user floor.
 */
bool elevator_ride(ES_INT user_floor, ES_INT target_floor);

/** @brief Function for advancing elevator system simulation by one step. */
void elevator_step(void);

/**
 * @brief Function for checking if there is requested elevator on the specified floor.
 *
 * @param floor Floor to check.
 *
 * @return True if there is an elevator on the specified floor, false otherwise.
 */
bool elevator_on_floor_check(ES_INT floor);

#endif /* ELEVATOR_H */