#include <stdio.h>
#include <stdlib.h>
#include <elevator_cli.h>
#include <elevator.h>
#include <string.h>

typedef bool (* input_validator_t)(void * input, void * output);

static bool operation_validator(void * input, void * output)
{
    char * p_char = input;
    if ((*p_char == 'c') || (*p_char == 'e') || (*p_char == 's'))
    {
        *(char *)output = *p_char;
        return true;
    }
    else
    {
        return false;
    }
}

static bool direction_validator(void * input, void * output)
{
    char * p_char = input;
    if ((*p_char == 'd') || (*p_char == 'u'))
    {
        *(char *)output = *p_char;
        return true;
    }
    else
    {
        return false;
    }
}

static bool floor_validator(void * input, void * output)
{
    int floor = atoi((const char *)input);
    if ((floor <= NUMBER_OF_FLOORS) && (floor >= 0))
    {
        *(int *)output = floor;
        return true;
    }
    else
    {
        return false;
    }
}

static void input_get_and_validate(char const * prompt, void * output, input_validator_t validator)
{
    bool status = false;
    char buf[128];

    while (!status)
    {
        printf("%s", prompt);
        fgets(buf, sizeof(buf), stdin);

        status = validator(buf, output);

        if (!status)
        {
            printf("Incorrect input\n");
        }
    }
}

static void show_elevators_status(void)
{
    printf("Elevator:       Current floor:  Target floor:\n");
    for (size_t i = 0; i<NUMBER_OF_ELEVATORS; i++)
    {
        printf("%8d %16d %16d\n", i, get_elevator_current_floor(i), get_elevator_target_floor(i));
    }
}

void elevator_cli_start(void)
{
    elevator_init();
    printf("ELEVATOR SYSTEM CLI\n");

    while (1)
    {
        char operation;
        char * operation_prompt = "What are you going to do?\n"
                                  "If you want to call the elevator type 'c'\n"
                                  "If you want to enter the elevator type 'e'\n"
                                  "If you want to advance the simulation by one step type 's'\n";
        input_get_and_validate(operation_prompt, &operation, operation_validator);

        printf("Operation: %c\n", operation);

        if (operation == 'c')
        {
            char direction;
            char * direction_prompt = "Which direction you want to go?\n"
                                      "Type 'u' for up or 'd' for down\n";
            input_get_and_validate(direction_prompt, &direction, direction_validator);

            printf("Direction: %c\n", direction);

            int current_floor;
            char * current_floor_prompt = "Enter the floor you are on\n";
            input_get_and_validate(current_floor_prompt, &current_floor, floor_validator);

            printf("Current floor: %d\n", current_floor);

            elevator_call(current_floor, direction == 'u' ? DIR_UP : DIR_DOWN);
        }
        else if (operation == 'e')
        {
            int current_floor;
            char * current_floor_prompt = "Enter the floor you are on\n";
            input_get_and_validate(current_floor_prompt, &current_floor, floor_validator);

            printf("Current floor: %d\n", current_floor);

            bool is_elev_on_current_floor = elevator_on_floor_check(current_floor);
            if (is_elev_on_current_floor)
            {
                int target_floor;
                char * target_floor_prompt = "Enter the floor you want to be on\n";
                input_get_and_validate(target_floor_prompt, &target_floor, floor_validator);

                printf("Target floor: %d\n", target_floor);

                (void)elevator_ride(current_floor, target_floor);
            }
            else
            {
                printf("There is no elevator on your floor\n");
                printf("Look at the list of elevators\n");
                show_elevators_status();
            }
        }
        else if (operation == 's')
        {
            elevator_step();
            show_elevators_status();
        }
    }
}