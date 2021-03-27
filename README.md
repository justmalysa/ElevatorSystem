# ElevatorSystem
Code for elevator system simulation

## Introduction

This repository contains source code, tests and sample application for a software that simulates several elevators working within single building.

## Prerequisites

In order to build tests or sample application, following tools are needed:
- `cmake`
- `ninja`
- `gcc`

Tools are expected to be added to system `PATH` variable.

## Capabilities

Library supports following functionalities:
- calling an elevator to specified floor together with choice of desired travel direction,
- checking whether elevator arrived on called floor,
- riding an elevator to specified floor after elevator arrival,
- getting the status of specified elevator,
- advancing the simulation by single step, that moves each elevator by single floor.

Elevator system algorithm traits:
- finds elevator that can reach called floor fastest,
- can send an idle elevator to called floor,
- can pick up a passenger that is on the way of an elevator that is already in motion,
- keeps track of all floors to be reached by given elevator, in case of multiple people inside,
- keeps track of all floors call, in case no elevator is able to serve the request at given simulation point.

## How to - library API

Initialize the elevator system (all elevators start on ground level):
```
elevator_init();
```

User is expected to feed the system with elevator calls (that is - calling an elevator to specified floor together with desired travel direction):
```
ES_INT user_floor = 3;
elevator_call(user_floor, DIR_UP);
```

Then simulation needs to be advanced by single or several steps, so the assigned elevators reach calling floors:
```
while (!elevator_on_floor_check(user_floor))
{
    elevator_step();
}
```

After elevator reaches calling floor, enter the elevator to ride inside to desired target floor:
```
ES_INT target_floor = 5;
assert(elevator_ride(user_floor, target_floor));
```

Another person can also enter the elevator at this point and choose different target floor:
```
target_floor_2nd = 7;
assert(elevator_ride(user_floor, target_floor_2nd));
```

Then simulation needs to be advanced by single or several steps, so the elevator takes the passengers to their target floors:
```
while (!elevator_on_floor_check(target_floor))
{
    elevator_step();
}

while (!elevator_on_floor_check(target_floor_2nd))
{
    elevator_step();
}
```

Elevator calls and rides can be freely intermixed in the process. Algorith will take care of correct elevator assignments.
User is just expected to monitor when an elevator arrives on his floor (`user_floor`) before trying to ride an elevator.

## How to - unit tests

Unit tests verify correctness of several predefined sequences of library API calls.
They are created using `Unity` framework (https://github.com/ThrowTheSwitch/Unity).

Clone the repository:
```
https://github.com/justmalysa/ElevatorSystem.git
```
or
```
git@github.com:justmalysa/ElevatorSystem.git
```

Enter `tests` directory:
```
cd ElevatorSystem/tests
```

Create and enter `build` directory:
```
mkdir build
cd build
```

Invoke `cmake`:
```
cmake -GNinja ..
```

Invoke `ninja` to compile the unit tests:
```
ninja
```

Run created `unit_test.elf` file to launch tests:
```
./unit_test.elf
```

Test result should be printed on terminal.

## How to - sample application

Sample application integrates elevator library with command-line interface to give the user opportunity to work with system interactively.

Clone the repository:
```
https://github.com/justmalysa/ElevatorSystem.git
```
or
```
git@github.com:justmalysa/ElevatorSystem.git
```

Enter `examples/cli` directory:
```
cd ElevatorSystem/examples/cli
```

Create and enter `build` directory:
```
mkdir build
cd build
```

Invoke `cmake`:
```
cmake -GNinja ..
```

Invoke `ninja` to compile the sample application:
```
ninja
```

Run created `cli_example.elf` file to launch application:
```
./cli_example.elf
```

Prompt message with further instructions should be printed on terminal.
