#include <unity.h>
#include <elevator.c>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_elevator_init(void)
{
    struct elevator_status test_arr[NUMBER_OF_ELEVATORS];
    memset(test_arr, 0, sizeof(test_arr));
    elevator_init();
    int result = memcmp(elevator_arr, test_arr, sizeof(elevator_arr));
    TEST_ASSERT_EQUAL(result, 0);
}

void test_elevator_call(void)
{
    int test_user_floor = 4;
    int test_direction = 1;

    elevator_init();
    elevator_call(test_user_floor, test_direction);
    TEST_ASSERT_TRUE(floor_arr[test_user_floor].is_requested);
    TEST_ASSERT_EQUAL(floor_arr[test_user_floor].direction, test_direction);
}

void test_elevator_ride(void)
{
    int test_user_floor = 0;
    int test_target_floor = 1;

    elevator_init();
    TEST_ASSERT_TRUE(elevator_ride(test_user_floor, test_target_floor));

    test_user_floor = 1;
    elevator_init();
    TEST_ASSERT_FALSE(elevator_ride(test_user_floor, test_target_floor));
}

void test_elevator_step(void)
{
    elevator_init();
    elevator_step();
    /* Nothing to expect */
}

void test_elevator_floor_reached_check(void)
{
    int test_elev_index = 7;

    elevator_init();
    TEST_ASSERT(elevator_floor_reached_check(test_elev_index));
}

void test_elevator_single_call_and_steps(void)
{
    int test_user_floor = 4;
    int test_direction = 1;
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

void test_elevator_single_call_steps_and_ride(void)
{
    int test_user_floor = 4;
    int test_user_target_floor = 6;
    int test_direction = 1;

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

void test_elevator_three_calls_steps_and_ride(void)
{
    int test_user_floor_1 = 0;
    int test_user_target_floor_1 = 4;
    int test_direction_1 = 1;

    int test_user_floor_2 = 9;
    int test_user_target_floor_2 = 6;
    int test_direction_2 = 0;

    int test_user_floor_3 = 7;
    int test_user_target_floor_3 = 4;
    int test_direction_3 = 0;

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

    TEST_ASSERT_FALSE(elevator_on_floor_check(test_user_target_floor_1));

    elevator_step();

    TEST_ASSERT_TRUE(elevator_on_floor_check(test_user_target_floor_1));

    elevator_step();
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

void test_elevator_single_call_steps_and_ride_with_initial_values(void)
{
    int test_user_floor = 5;
    int test_user_target_floor = 7;
    int test_direction = 1;

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

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_elevator_init);
    RUN_TEST(test_elevator_call);
    RUN_TEST(test_elevator_ride);
    RUN_TEST(test_elevator_step);
    RUN_TEST(test_elevator_floor_reached_check);
    RUN_TEST(test_elevator_single_call_and_steps);
    RUN_TEST(test_elevator_single_call_steps_and_ride);
    RUN_TEST(test_elevator_three_calls_steps_and_ride);
    RUN_TEST(test_elevator_single_call_steps_and_ride_with_initial_values);

    return UNITY_END();
}
