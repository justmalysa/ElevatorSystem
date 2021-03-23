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
    struct elevator_status test_tab[NUMBER_OF_ELEVATORS];
    memset(test_tab, 0, sizeof(test_tab));
    elevator_init();
    int result = memcmp(elevator_tab, test_tab, sizeof(elevator_tab));
    TEST_ASSERT_EQUAL(result, 0);
}

void test_elevator_call(void)
{
    int test_user_floor = 4;
    int test_direction = 1;

    elevator_init();
    int elev_index = elevator_call(test_user_floor, test_direction);
    TEST_ASSERT_EQUAL(elev_index, 0);
    TEST_ASSERT_EQUAL(elevator_tab[elev_index].target_floor, test_user_floor);
}

void test_elevator_ride(void)
{
    int test_elev_index = 4;
    int test_target_floor = 6;

    elevator_init();
    elevator_ride(test_elev_index, test_target_floor);
    TEST_ASSERT_EQUAL(elevator_tab[test_elev_index].target_floor, test_target_floor);
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

void test_elevator_call_and_steps(void)
{
    int test_user_floor = 4;
    int test_direction = 1;
    int elev_index;

    elevator_init();
    elev_index = elevator_call(test_user_floor, test_direction);
    elevator_step();
    elevator_step();
    elevator_step();

    TEST_ASSERT_FALSE(elevator_floor_reached_check(elev_index));
    elevator_step();
    TEST_ASSERT_TRUE(elevator_floor_reached_check(elev_index));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_elevator_init);
    RUN_TEST(test_elevator_call);
    RUN_TEST(test_elevator_ride);
    RUN_TEST(test_elevator_step);
    RUN_TEST(test_elevator_floor_reached_check);
    RUN_TEST(test_elevator_call_and_steps);

    return UNITY_END();
}
