cmake_minimum_required(VERSION 3.20)
project(philo C)

set(CMAKE_C_STANDARD 99)

add_executable(philo
        philo/philo.c
        philo/init.c
        philo/routine.c
        philo/time_management.c
        philo/utils.c)

SET(CMAKE_C_FLAGS " ${CMAKE_C_FLAGS} -Wall -Wextra -fsanitize=thread")
#SET(CMAKE_C_FLAGS " ${CMAKE_C_FLAGS} -Wall -Wextra")