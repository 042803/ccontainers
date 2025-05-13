cmake_minimum_required(VERSION 3.10)

project(ccontainers_vector)

set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

# Core library
add_library(cds STATIC
    src/array.c
    src/array_utils.c
    src/binop.c
    src/algo.c
    src/comparators.c
    src/main.c
    src/math.c
    src/msc.c
    src/search.c
)

target_include_directories(cds PUBLIC include)

# CUnit
find_library(CUNIT_LIBRARY cunit)
find_path(CUNIT_INCLUDE_DIR CUnit/CUnit.h)

include_directories(${CUNIT_INCLUDE_DIR})

# Test discovery
file(GLOB UNIT_TESTS_UNIT "tests/unit/*.c")
file(GLOB UNIT_TESTS_STRESS "tests/stress/*.c")
set(UNIT_TESTS ${UNIT_TESTS_UNIT} ${UNIT_TESTS_STRESS})

# Build each test
foreach(test_file ${UNIT_TESTS})
    get_filename_component(test_name ${test_file} NAME_WE)

    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} cds ${CUNIT_LIBRARY})
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

enable_testing()
