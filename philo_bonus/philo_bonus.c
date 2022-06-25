#include "includes/philo_bonus.h"

static int satiety_all(t_info *info)
{
	int i;

	i = 0;
	while(i < info->philo_num)
	{
		if (info->philo[i].meal_count < info->philo_must_eat)
			return (0);
		i++;
	}
	return (1);
}

static int	satiety_philo(t_info *info)
{
	int i;

	while (1)
	{
		i = 0;
		while (i < info->philo_num)
		{
			sem_wait(info->philo[i].eaten);
			info->philo[i].meal_count++;
			if ((info->philo[i].meal_count == info->philo_must_eat) &&
					(satiety_all(info) == 1))
			{
				i = 0;
				while (i < info->philo_num)
				{
					kill(info->philo[i].pid, SIGTERM);
					i++;
				}
				exit(0);
			}
		}
		usleep(500);
	}
}

int	are_you_dead(t_philo *philo)
{
	struct timeval	current;
	long long		long_current;
	long long		long_meal_time;

	gettimeofday(&current, NULL);
	long_current = time_converter(&current);
	long_meal_time = time_converter(&philo->meal_time);
	return ((long_current - long_meal_time) >= philo->info->time_to_die);
}

void	*philo_monitoring(void *p)
{
	t_philo	*philo;

	philo = p;
	while (1)
	{
		if (are_you_dead(philo)) // TODO semaphores in function are_yuo_dead
		{
			status_print(philo->info, philo->philo_id, "died");
			exit (1); // TODO ?? X3 do we need 1 or not?
		}
		usleep(500);
	}
}


int	main(int argc, char *argv[])
{
	t_info	info;
	t_philo	*philo;
	int		i;

	i = 0;
	memset(&info, 0, sizeof(info));
	if (argc != 5 && argc != 6)
		return (error_printf("ERROR: wrong argc"));
	if (init(&info, &philo, argc, argv))
	{
		free(info.forks);
		info.forks = NULL;
		return (EXIT_FAILURE);
	}
	while(i < info.philo_num)
	{
		info.philo[i].pid = fork();
		if (info.philo[i].pid == 0)
			routine(&info, i);
		i++;
	}
	if (info.philo_must_eat != 0)
	{
		info.pid_satiety = fork();
		if (info.pid_satiety == 0)
			satiety_philo(&info);
	}
	wait_kill_clean(&info, info.pid_satiety);
	return (0);
}
