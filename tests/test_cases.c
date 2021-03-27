#include <unity.h>
#include <elevator.c>

void setUp(void)
{
}

void tearDown(void)
{
}

/**
 * @brief Function for checking @ref elevator_init() function.
 *
 * Test initializes elevator system and check if all internal variable are zero.
 */
void test_elevator_init(void)
{
    struct elevator_status test_arr[NUMBER_OF_ELEVATORS];
    memset(test_arr, 0, sizeof(test_arr));
    elevator_init();
    ES_INT result = memcmp(elevator_arr, test_arr, sizeof(elevator_arr));
    TEST_ASSERT_EQUAL(result, 0);
}

/**
 * @brief Function for checking @ref elevator_call() function.
 *
 * Test calls an elevator and checks whether internal variables are correctly updated.
 */
void test_elevator_call(void)
{
    ES_INT test_user_floor = 4;
    ES_INT test_direction = DIR_UP;

    elevator_init();
    elevator_call(test_user_floor, test_direction);
    TEST_ASSERT_TRUE(floor_arr[test_user_floor].is_requested);
    TEST_ASSERT_EQUAL(floor_arr[test_user_floor].direction, test_direction);
}

/**
 * @brief Function for checking @ref elevator_ride() function.
 *
 * Test attempts to use an elevator on ground and first floor,
 * then checks whether the operation was successful or not.
 */
void test_elevator_ride(void)
{
    ES_INT test_user_floor = 0;
    ES_INT test_target_floor = 1;

    elevator_init();
    TEST_ASSERT_TRUE(elevator_ride(test_user_floor, test_target_floor));

    test_user_floor = 1;
    elevator_init();
    TEST_ASSERT_FALSE(elevator_ride(test_user_floor, test_target_floor + 1));
}

/**
 * @brief Function for checking elevator operation after being called.
 *
 * Test calls the elevator to 4th floor and expects the elevator
 * to reach the floor after four simulation steps.
 */
void test_one_elevator_call_without_ride(void)
{
    ES_INT test_user_floor = 4;
    ES_INT test_direction = DIR_UP;
    ES_INT elev_index;

    elevator_init();
    elevator_call(test_user_floor, test_direction);

    elevator_step();
    elevator_step();
    elevator_step();

    TEST_ASSERT_FALSE(elevator_on_floor_check(test_user_floor));
    elevator_step();
    TEST_ASSERT_TRUE(elevator_on_floor_check(test_user_floor));
}

/**
 * @brief Function for checking elevator operation for call and ride.
 *
 * Test calls the elevator to 4th floor and expects the elevator
 * to reach the floor after four simulation steps.
 * Then the elevator is used to travel to 6th floor.
 */
void test_one_elevator_with_default_values(void)
{
    ES_INT test_user_floor = 4;
    ES_INT test_user_target_floor = 6;
    ES_INT test_direction = DIR_UP;

    elevator_init();
    elevator_call(test_user_floor, test_direction);

    elevator_step();
    elevator_step();
    elevator_step();
    elevator_step();

    TEST_ASSERT_TRUE(elevator_on_floor_check(test_user_floor));

    TEST_ASSERT(elevator_ride(test_user_floor, test_user_target_floor));

    elevator_step();
    TEST_ASSERT_FALSE(elevator_on_floor_check(test_user_target_floor));
    elevator_step();
    TEST_ASSERT_TRUE(elevator_on_floor_check(test_user_target_floor));
}

/**
 * @brief Function for checking three elevators operation for call and ride.
 *
 * Test calls three elevators to specified floors.
 * After arrival, elevators are used to travel to floors chosen by the users.
 */
void test_three_elevators_with_default_values(void)
{
    ES_INT test_user_floor_1 = 0;
    ES_INT test_user_target_floor_1 = 5;
    ES_INT test_direction_1 = DIR_UP;

    ES_INT test_user_floor_2 = 9;
    ES_INT test_user_target_floor_2 = 6;
    ES_INT test_direction_2 = DIR_DOWN;

    ES_INT test_user_floor_3 = 7;
    ES_INT test_user_target_floor_3 = 4;
    ES_INT test_direction_3 = DIR_DOWN;

    elevator_init();

    elevator_call(test_user_floor_1, test_direction_1);
    elevator_call(test_user_floor_2, test_direction_2);
    elevator_call(test_user_floor_3, test_direction_3);

    elevator_step();

    TEST_ASSERT_TRUE(elevator_on_floor_check(test_user_floor_1));

    TEST_ASSERT(elevator_ride(test_user_floor_1, test_user_target_floor_1));

    elevator_step();
    elevator_step();
    elevator_step();
    elevator_step();

    TEST_ASSERT_FALSE(elevator_on_floor_check(test_user_target_floor_1));

    elevator_step();

    TEST_ASSERT_TRUE(elevator_on_floor_check(test_user_target_floor_1));

    elevator_step();

    TEST_ASSERT_TRUE(elevator_on_floor_check(test_user_floor_3));
    TEST_ASSERT(elevator_ride(test_user_floor_3, test_user_target_floor_3));

    elevator_step();
    elevator_step();

    TEST_ASSERT_FALSE(elevator_on_floor_check(test_user_target_floor_3));
    TEST_ASSERT_TRUE(elevator_on_floor_check(test_user_floor_2));
    TEST_ASSERT(elevator_ride(test_user_floor_2, test_user_target_floor_2));

    elevator_step();

    TEST_ASSERT_TRUE(elevator_on_floor_check(test_user_target_floor_3));

    elevator_step();

    TEST_ASSERT_FALSE(elevator_on_floor_check(test_user_target_floor_2));

    elevator_step();
    TEST_ASSERT_TRUE(elevator_on_floor_check(test_user_target_floor_2));
}

/**
 * @brief Function for checking elevator operation for call and ride with non-ground starting floor.
 *
 * Test calls the elevator to 5th floor and expects the elevator
 * to reach the floor after five simulation steps.
 * Then the elevator is used to travel to 7th floor.
 */
void test_one_elevator_with_preset_values(void)
{
    ES_INT test_user_floor = 5;
    ES_INT test_user_target_floor = 7;
    ES_INT test_direction = DIR_UP;

    elevator_init();
    elevator_arr[2].current_floor = 4;
    elevator_arr[2].target_floor = 8;

    elevator_call(test_user_floor, test_direction);

    elevator_step();

    TEST_ASSERT_TRUE(elevator_on_floor_check(test_user_floor));

    TEST_ASSERT(elevator_ride(test_user_floor, test_user_target_floor));

    elevator_step();
    TEST_ASSERT_FALSE(elevator_on_floor_check(test_user_target_floor));
    elevator_step();
    TEST_ASSERT_TRUE(elevator_on_floor_check(test_user_target_floor));
}

/**
 * @brief Function for checking two elevators operation for call and ride with non-ground starting floor.
 *
 * Test calls two elevators to specified floors.
 * After arrival, elevators are used to travel to floors chosen by the users.
 */
void test_two_elevators_with_preset_values(void)
{
    ES_INT test_user_floor_1 = 8;
    ES_INT test_user_target_floor_1 = 6;
    ES_INT test_direction_1 = DIR_DOWN;

    ES_INT test_user_floor_2 = 2;
    ES_INT test_user_target_floor_2 = 3;
    ES_INT test_direction_2 = DIR_UP;

    elevator_init();
    elevator_arr[4].current_floor = 7;
    elevator_arr[4].target_floor = 9;
    elevator_arr[4].requested_floors[9] = true;

    elevator_arr[0].current_floor = 0;
    elevator_arr[0].target_floor = 4;
    elevator_arr[0].requested_floors[4] = true;

    elevator_arr[7].current_floor = 10;
    elevator_arr[7].target_floor = 5;
    elevator_arr[7].requested_floors[5] = true;

    elevator_call(test_user_floor_1, test_direction_1);
    elevator_call(test_user_floor_2, test_direction_2);

    elevator_step();
    TEST_ASSERT_EQUAL(elevator_arr[4].current_floor, 8);
    TEST_ASSERT_EQUAL(elevator_arr[0].current_floor, 1);
    TEST_ASSERT_EQUAL(elevator_arr[7].current_floor, 9);

    elevator_step();
    TEST_ASSERT_EQUAL(elevator_arr[4].current_floor, 9);
    TEST_ASSERT_EQUAL(elevator_arr[0].current_floor, 2);
    TEST_ASSERT_EQUAL(elevator_arr[7].current_floor, 8);

    TEST_ASSERT_TRUE(elevator_on_floor_check(test_user_floor_1));
    TEST_ASSERT(elevator_ride(test_user_floor_1, test_user_target_floor_1));

    TEST_ASSERT_TRUE(elevator_on_floor_check(test_user_floor_2));

    TEST_ASSERT(elevator_ride(test_user_floor_2, test_user_target_floor_2));

    TEST_ASSERT_FALSE(elevator_on_floor_check(test_user_target_floor_2));

    elevator_step();
    TEST_ASSERT_EQUAL(elevator_arr[0].current_floor, 3);
    TEST_ASSERT_EQUAL(elevator_arr[7].current_floor, 7);

    TEST_ASSERT_TRUE(elevator_on_floor_check(test_user_target_floor_2));
    TEST_ASSERT_FALSE(elevator_on_floor_check(test_user_target_floor_1));

    elevator_step();
    TEST_ASSERT_EQUAL(elevator_arr[0].current_floor, 4);
    TEST_ASSERT_EQUAL(elevator_arr[7].current_floor, 6);

    TEST_ASSERT_TRUE(elevator_on_floor_check(test_user_target_floor_1));

    elevator_step();
    TEST_ASSERT_EQUAL(elevator_arr[7].current_floor, 5);
}

/**
 * @brief Function for checking single elevator operation for two passengers entering elevator on same floor.
 *
 * Test calls elevator to specified floor.
 * After arrival, two passengers enter the elevator and choose different floors.
 */
void test_one_elevator_two_passengers_same_ride_floor(void)
{
    elevator_init();

    ES_INT user_floor = 3;
    ES_INT target_floor_1 = 5;
    ES_INT target_floor_2 = 7;
    elevator_call(user_floor, DIR_UP);

    elevator_step();
    elevator_step();
    TEST_ASSERT_FALSE(elevator_on_floor_check(user_floor));
    elevator_step();
    TEST_ASSERT_TRUE(elevator_on_floor_check(user_floor));

    TEST_ASSERT(elevator_ride(user_floor, target_floor_1));
    TEST_ASSERT(elevator_ride(user_floor, target_floor_2));

    elevator_step();
    TEST_ASSERT_FALSE(elevator_on_floor_check(target_floor_1));
    elevator_step();
    TEST_ASSERT_TRUE(elevator_on_floor_check(target_floor_1));

    elevator_step();
    TEST_ASSERT_FALSE(elevator_on_floor_check(target_floor_2));
    elevator_step();
    TEST_ASSERT_TRUE(elevator_on_floor_check(target_floor_2));
}

/**
 * @brief Function for checking single elevator operation for two passengers entering elevator on different floor.
 *
 * Test calls elevator to specified floor.
 * After arrival, one of the passengers enter the elevator.
 * Then another passenger calls the elevator from floor that is on the way of the previously called elevator.
 * Elevator stops to handle second passenger on his floor and then proceeds to go to target floors of both passengers.
 */
void test_one_elevator_two_passengers_different_ride_floor(void)
{
    elevator_init();

    ES_INT user_floor_1 = 1;
    ES_INT user_floor_2 = 3;
    ES_INT target_floor_1 = 7;
    ES_INT target_floor_2 = 5;

    elevator_call(user_floor_1, DIR_UP);

    elevator_step();
    TEST_ASSERT_TRUE(elevator_on_floor_check(user_floor_1));
    TEST_ASSERT(elevator_ride(user_floor_1, target_floor_1));

    elevator_call(user_floor_2, DIR_UP);

    elevator_step();
    elevator_step();
    TEST_ASSERT_TRUE(elevator_on_floor_check(user_floor_2));
    TEST_ASSERT(elevator_ride(user_floor_2, target_floor_2));

    elevator_step();
    elevator_step();
    TEST_ASSERT_TRUE(elevator_on_floor_check(target_floor_2));

    elevator_step();
    elevator_step();
    TEST_ASSERT_TRUE(elevator_on_floor_check(target_floor_1));
}

/**
 * @brief Function for checking single elevator operation for two passengers but one of them chooses incorrect direction.
 *
 * Test calls elevator to specified floor.
 * After arrival, one of the passengers enter the elevator and chooses target floor that matches previously chosen direction.
 * Another passenger also attempts to enter the elevator, but it does not match the elevator direction.
 */
void test_one_elevator_two_passengers_wrong_dir(void)
{
    elevator_init();

    ES_INT user_floor = 3;
    ES_INT target_floor_1 = 5;
    ES_INT target_floor_2 = 2;
    elevator_call(user_floor, DIR_UP);

    elevator_step();
    elevator_step();
    TEST_ASSERT_FALSE(elevator_on_floor_check(user_floor));
    elevator_step();
    TEST_ASSERT_TRUE(elevator_on_floor_check(user_floor));

    TEST_ASSERT_TRUE(elevator_ride(user_floor, target_floor_1));
    TEST_ASSERT_FALSE(elevator_ride(user_floor, target_floor_2));

    elevator_step();
    TEST_ASSERT_FALSE(elevator_on_floor_check(target_floor_1));
    elevator_step();
    TEST_ASSERT_TRUE(elevator_on_floor_check(target_floor_1));
    elevator_step();
    TEST_ASSERT_TRUE(elevator_on_floor_check(target_floor_1));
}

/**
 * @brief Function for checking whether elevator can switch direction after reaching its top-most target floor.
 *
 * Test calls elevator to specified floor.
 * After arrival, one of the passengers enter the elevator and chooses target floor.
 * After arriving on target floor, another passenger enters the elevator and wishes to go downwards.
 */
void test_one_elevator_two_passengers_dir_switch(void)
{
    elevator_init();

    ES_INT user_floor_1 = 3;
    ES_INT user_floor_2 = 5;
    ES_INT target_floor_1 = 5;
    ES_INT target_floor_2 = 2;

    elevator_call(user_floor_1, DIR_UP);

    elevator_step();
    elevator_step();
    TEST_ASSERT_FALSE(elevator_on_floor_check(user_floor_1));
    elevator_step();
    TEST_ASSERT_TRUE(elevator_on_floor_check(user_floor_1));

    TEST_ASSERT_TRUE(elevator_ride(user_floor_1, target_floor_1));

    elevator_step();
    TEST_ASSERT_FALSE(elevator_on_floor_check(target_floor_1));
    elevator_step();
    TEST_ASSERT_TRUE(elevator_on_floor_check(target_floor_1));

    TEST_ASSERT_TRUE(elevator_ride(user_floor_2, target_floor_2));
    elevator_step();
    elevator_step();
    elevator_step();
    TEST_ASSERT_TRUE(elevator_on_floor_check(target_floor_2));
}

/**
 * @brief Function for checking whether elevator correctly handles being called but not being ridden.
 *
 * Test calls elevator to specified floor.
 * After arrival, one passenger enter the elevator and chooses target floor.
 * At the same time another passenger calls the elevator to the floor
 * that matches direction of an elevator already moving.
 * Elevator tries to handle the call, but after arriving second passenger does not enter the elevator.
 * On next simulation step elevator should continue its journey with first passenger.
 */
void test_one_elevator_two_passengers_missed_ride(void)
{
    elevator_init();

    ES_INT user_floor_1 = 1;
    ES_INT user_floor_2 = 3;
    ES_INT target_floor_1 = 7;
    ES_INT target_floor_2 = 5;

    elevator_call(user_floor_1, DIR_UP);

    elevator_step();
    TEST_ASSERT_TRUE(elevator_on_floor_check(user_floor_1));
    TEST_ASSERT(elevator_ride(user_floor_1, target_floor_1));

    elevator_call(user_floor_2, DIR_UP);

    elevator_step();
    elevator_step();
    TEST_ASSERT_TRUE(elevator_on_floor_check(user_floor_2));
    /* Second user does not enter elevator despite calling it. */

    elevator_step();
    elevator_step();
    TEST_ASSERT_FALSE(elevator_on_floor_check(target_floor_2));

    elevator_step();
    elevator_step();
    TEST_ASSERT_TRUE(elevator_on_floor_check(target_floor_1));
}

/**
 * @brief Function for checking whether passenger can enter the elevator that wasn't called and is in motion.
 *
 * Test calls elevator to specified floor.
 * After arrival, one passenger enter the elevator and chooses target floor.
 * During the travel, another passenger tries to enter the elevator that passes its floor,
 * without prior call.
 */
void test_enter_non_called_non_idle_elevator(void)
{
    elevator_init();

    ES_INT user_floor_1 = 3;
    ES_INT user_floor_2 = 4;
    ES_INT target_floor_1 = 5;
    ES_INT target_floor_2 = 6;

    elevator_call(user_floor_1, DIR_UP);
    elevator_step();
    elevator_step();
    elevator_step();

    TEST_ASSERT_TRUE(elevator_on_floor_check(user_floor_1));
    TEST_ASSERT_TRUE(elevator_ride(user_floor_1, target_floor_1));

    elevator_step();

    TEST_ASSERT_FALSE(elevator_on_floor_check(user_floor_2));

    elevator_step();
    TEST_ASSERT_TRUE(elevator_on_floor_check(target_floor_1));
    elevator_step();
    TEST_ASSERT_TRUE(elevator_on_floor_check(target_floor_1));
}

ES_INT main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_elevator_init);
    RUN_TEST(test_elevator_call);
    RUN_TEST(test_elevator_ride);
    RUN_TEST(test_one_elevator_call_without_ride);
    RUN_TEST(test_one_elevator_with_default_values);
    RUN_TEST(test_three_elevators_with_default_values);
    RUN_TEST(test_one_elevator_with_preset_values);
    RUN_TEST(test_two_elevators_with_preset_values);
    RUN_TEST(test_one_elevator_two_passengers_same_ride_floor);
    RUN_TEST(test_one_elevator_two_passengers_different_ride_floor);
    RUN_TEST(test_one_elevator_two_passengers_wrong_dir);
    RUN_TEST(test_one_elevator_two_passengers_dir_switch);
    RUN_TEST(test_one_elevator_two_passengers_missed_ride);
    RUN_TEST(test_enter_non_called_non_idle_elevator);

    return UNITY_END();
}
