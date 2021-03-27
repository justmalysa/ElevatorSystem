cmake_minimum_required(VERSION 3.13.1)

add_executable(unit_test)
set_target_properties(unit_test PROPERTIES
    OUTPUT_NAME unit_test
    SUFFIX .elf
)

set(PROJECT_ROOT_DIR "..")

target_sources(unit_test PRIVATE
    ${PROJECT_ROOT_DIR}/tests/test_cases.c
    ${PROJECT_ROOT_DIR}/tests/unity/unity.c
)

target_include_directories(unit_test PRIVATE
    ${PROJECT_ROOT_DIR}/src
    ${PROJECT_ROOT_DIR}/inc
    ${PROJECT_ROOT_DIR}/tests/unity
)

list(APPEND C_FLAGS "--std=c99")
target_compile_options(unit_test PRIVATE ${C_FLAGS})

project(unit_test)
