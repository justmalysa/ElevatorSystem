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
    int result = memcmp(elevator_arr, test_arr, sizeof(elevator_arr));
    TEST_ASSERT_EQUAL(result, 0);
}

/**
 * @brief Function for checking @ref elevator_call() function.
 *
 * Test calls an elevator and checks whether internal variables are correctly updated.
 */
void test_elevator_call(void)
{
    int test_user_floor = 4;
    int test_direction = DIR_UP;

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
    int test_user_floor = 0;
    int test_target_floor = 1;

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
    int test_user_floor = 4;
    int test_direction = DIR_UP;
    int elev_index;

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
    int test_user_floor = 4;
    int test_user_target_floor = 6;
    int test_direction = DIR_UP;

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
    int test_user_floor_1 = 0;
    int test_user_target_floor_1 = 5;
    int test_direction_1 = DIR_UP;

    int test_user_floor_2 = 9;
    int test_user_target_floor_2 = 6;
    int test_direction_2 = DIR_DOWN;

    int test_user_floor_3 = 7;
    int test_user_target_floor_3 = 4;
    int test_direction_3 = DIR_DOWN;

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
    int test_user_floor = 5;
    int test_user_target_floor = 7;
    int test_direction = DIR_UP;

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
    int test_user_floor_1 = 8;
    int test_user_target_floor_1 = 6;
    int test_direction_1 = DIR_DOWN;

    int test_user_floor_2 = 2;
    int test_user_target_floor_2 = 3;
    int test_direction_2 = DIR_UP;

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

int main(void)
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

    return UNITY_END();
}
