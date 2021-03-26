#ifndef ELEVATOR_CONFIG_H
#define ELEVATOR_CONFIG_H

#ifndef NUMBER_OF_ELEVATORS
/** @brief Symbol specifying total number of elevators in the system. */
#define NUMBER_OF_ELEVATORS  16
#endif

#ifndef NUMBER_OF_FLOORS
/** @brief Symbol specifying total number of floors in the system. */
#define NUMBER_OF_FLOORS     20
#endif

#ifdef __CORTEX_M
#include <stdint.h>
typedef int32_t  ES_INT;
typedef uint32_t ES_SIZE_T;
#else
#include <stddef.h>
typedef int    ES_INT;
typedef size_t ES_SIZE_T;
#endif

#endif /* ELEVATOR_CONFIG_H */