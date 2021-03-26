cmake_minimum_required(VERSION 3.13.1)

add_executable(cli_example)
set_target_properties(cli_example PROPERTIES
    OUTPUT_NAME cli_example
    SUFFIX .elf
)

set(PROJECT_ROOT_DIR "../..")

target_sources(cli_example PRIVATE
    ${PROJECT_ROOT_DIR}/src/elevator.c
    ${PROJECT_ROOT_DIR}/src/elevator_cli.c
    ${PROJECT_ROOT_DIR}/examples/cli/main.c
)

target_include_directories(cli_example PRIVATE
    ${PROJECT_ROOT_DIR}/inc
)

list(APPEND C_FLAGS "--std=c99")
target_compile_options(cli_example PRIVATE ${C_FLAGS})

project(cli_example)
