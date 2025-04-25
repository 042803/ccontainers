
cmake_minimum_required(VERSION 3.10)

project(vector)

set(CMAKE_C_STANDARD 11)

set(CMAKE_BUILD_TYPE Debug)

include_directories(include)

add_library(cds STATIC
    src/array.c
    src/array_utils.c
    src/binop.c
    src/comparators.c
    src/main.c
    src/math.c
    src/msc.c
    src/search.c
)

file(GLOB UNIT_TESTS "tests/unit/*.c")


include_directories(/usr/include/CUnit)

link_directories(/usr/lib)

foreach(test_file ${UNIT_TESTS})
    get_filename_component(test_name ${test_file} NAME_WE)

    add_executable(${test_name} ${test_file})

    target_link_libraries(${test_name} cds /usr/lib/libcunit.so)

    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
enable_testing()

