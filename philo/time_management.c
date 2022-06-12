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

void	my_sleep(int ms)
{
	long long	time;

	time = get_time();
	usleep(ms * 920);
	while (get_time() < time + ms)
		usleep(ms * 2);
}