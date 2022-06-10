#include "includes/philo.h"

long long	time_converter(struct timeval *time)
{
	return(time->tv_sec * 1000 + time->tv_usec);
}
