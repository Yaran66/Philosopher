cmake_minimum_required(VERSION 3.20)
project(philo C)

set(CMAKE_C_STANDARD 99)

add_executable(philo
        philo/philo.c
        philo/init.c
        philo/routine.c
        philo/time_management.c
        philo/utils.c)

add_executable(philo_bonus
        philo_bonus/philo_bonus.c
        philo_bonus/init_bonus.c
        philo_bonus/routine_bonus.c
        philo_bonus/time_management_bonus.c
        philo_bonus/utils_bonus.c)

SET(CMAKE_C_FLAGS " ${CMAKE_C_FLAGS} -Wall -Wextra -fsanitize=thread")
#SET(CMAKE_C_FLAGS " ${CMAKE_C_FLAGS} -Wall -Wextra")