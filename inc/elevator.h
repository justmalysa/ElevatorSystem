#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <stdbool.h>

/** @brief Symbol specifying total number of elevators in the system. */
#define NUMBER_OF_ELEVATORS  16

/** @brief Symbol specifying total number of floors in the system. */
#define NUMBER_OF_FLOORS     20

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
int get_elevator_current_floor(int elev_index);

/**
 * @brief Function for getting target floor of the specified elevator.
 *
 * @param elev_index Index of the elevator to be checked.
 *
 * @return Elevator target floor.
 */
int get_elevator_target_floor(int elev_index);

/** @brief Function for initializing elevator system. */
void elevator_init(void);

/**
 * @brief Function for calling the elevator to the specified floor.
 *
 * @param user_floor Floor to which elevator is called.
 * @param direction  Direction of the elevator call.
 *                   Can be @ref DIR_UP or @ref DIR_DOWN.
 */
void elevator_call(int user_floor, int direction);

/**
 * @brief Function for entering the elevator and choosing a desired floor.
 *
 * @param user_floor   Floor on which user is entering the elevator.
 * @param target_floor User desired floor.
 *
 * @retval true  Operation was successful.
 * @retval false There isn't any elevator on the user floor.
 */
bool elevator_ride(int user_floor, int target_floor);

/** @brief Function for advancing elevator system simulation by one step. */
void elevator_step(void);

/**
 * @brief Function for checking if there is requested elevator on the specified floor.
 *
 * @param floor Floor to check.
 *
 * @return True if there is an elevator on the specified floor, false otherwise.
 */
bool elevator_on_floor_check(int floor);

#endif /* ELEVATOR_H */