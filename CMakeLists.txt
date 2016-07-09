cmake_minimum_required(VERSION 3.2)
project(tdd_cata C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES
    main.c)

add_executable(tdd_cata ${SOURCE_FILES})
