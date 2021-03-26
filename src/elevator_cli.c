#include <stdio.h>
#include <stdlib.h>
#include <elevator_cli.h>
#include <elevator.h>
#include <string.h>

/**
 * @brief Type describing pointer to a function used for validating user input.
 *
 * @param[in]  input  Pointer to the array of chars, representing user input.
 * @param[out] output Pointer to memory to be filled with parsed data.
 *
 * @return True if user input was correct, false otherwise.
 */
typedef bool (* input_validator_t)(void * input, void * output);

/**
 * @brief Function for validating user input that regards elevator operation choice.
 *
 * @param[in]  input  Pointer to the array of chars, representing user input.
 * @param[out] output Pointer to memory to be filled with parsed data.
 *
 * @return True if user input was correct, false otherwise.
 */
static bool operation_validator(void * input, void * output)
{
    char * p_char = input;
    if ((*p_char == 'c') || (*p_char == 'e') || (*p_char == 's') || (*p_char == 'p'))
    {
        *(char *)output = *p_char;
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Function for validating user input that regards elevator direction choice.
 *
 * @param[in]  input  Pointer to the array of chars, representing user input.
 * @param[out] output Pointer to memory to be filled with parsed data.
 *
 * @return True if user input was correct, false otherwise.
 */
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

/**
 * @brief Function for validating user input that regards floor choice.
 *
 * @param[in]  input  Pointer to the array of chars, representing user input.
 * @param[out] output Pointer to memory to be filled with parsed data.
 *
 * @return True if user input was correct, false otherwise.
 */
static bool floor_validator(void * input, void * output)
{
    ES_INT floor = atoi((const char *)input);
    if ((floor <= NUMBER_OF_FLOORS) && (floor >= 0))
    {
        *(ES_INT *)output = floor;
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Function for getting and validating user input.
 *
 * @param[in]  prompt    Pointer to the array of chars, representing prompt message.
 * @param[out] output    Pointer to memory to be filled with parsed input data.
 * @param[in]  validator Pointer to the function to be used to validate the user input.
 */
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

/** @brief Function showing status of all of the elevators. */
static void show_elevators_status(void)
{
    printf("Elevator:       Current floor:  Target floor:\n");
    for (ES_SIZE_T i = 0; i<NUMBER_OF_ELEVATORS; i++)
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
                                  "If you want to advance the simulation by one step type 's'\n"
                                  "If you want to print elevators status type 'p'\n";
        input_get_and_validate(operation_prompt, &operation, operation_validator);

        printf("Operation: %c\n", operation);

        if (operation == 'c')
        {
            char direction;
            char * direction_prompt = "Which direction you want to go?\n"
                                      "Type 'u' for up or 'd' for down\n";
            input_get_and_validate(direction_prompt, &direction, direction_validator);

            printf("Direction: %c\n", direction);

            ES_INT current_floor;
            char * current_floor_prompt = "Enter the floor you are on\n";
            input_get_and_validate(current_floor_prompt, &current_floor, floor_validator);

            printf("Current floor: %d\n", current_floor);

            elevator_call(current_floor, direction == 'u' ? DIR_UP : DIR_DOWN);
        }
        else if (operation == 'e')
        {
            ES_INT current_floor;
            char * current_floor_prompt = "Enter the floor you are on\n";
            input_get_and_validate(current_floor_prompt, &current_floor, floor_validator);

            printf("Current floor: %d\n", current_floor);

            bool is_elev_on_current_floor = elevator_on_floor_check(current_floor);
            if (is_elev_on_current_floor)
            {
                ES_INT target_floor;
                char * target_floor_prompt = "Enter the floor you want to be on\n";
                input_get_and_validate(target_floor_prompt, &target_floor, floor_validator);

                printf("Target floor: %d\n", target_floor);

                (void)elevator_ride(current_floor, target_floor);
            }
            else
            {
                printf("There is no elevator on your floor\n"
                       "Look at the list of elevators:\n");
                show_elevators_status();
            }
        }
        else if (operation == 's')
        {
            elevator_step();
        }
        else if (operation == 'p')
        {
            show_elevators_status();
        }
    }
}