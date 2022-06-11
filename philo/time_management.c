#include "includes/philo.h"

long long	time_converter(struct timeval *time)
{
	return(time->tv_sec * 1000 + (time->tv_usec / 1000));
}

long long	get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (time_converter(&tv));
}