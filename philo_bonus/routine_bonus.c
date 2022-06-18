#include "includes/philo_bonus.h"

void	choose_fork(t_philo *philo, int *first_fork, int *second_fork)
{
	if (philo->philo_id == 1)
	{
		*first_fork = 0;
		*second_fork = philo->info->philo_num - 1;
	}
	else
	{
		*first_fork = philo->philo_id - 2;
		*second_fork = philo->philo_id - 1;
	}
}

void	status_print(t_info *info, int id, char *status)
{
	long long	time_stat;

	time_stat = get_time() - time_converter(&info->start_prog);
	pthread_mutex_lock(&info->print);
	pthread_mutex_lock(&info->protect_flag);
	if (info->exit_flag)
	{
		if (!ft_strncmp(status, "died", 5))
			printf("%lld %d %s\n", time_stat, id, status);
		pthread_mutex_unlock(&info->protect_flag);
		pthread_mutex_unlock(&info->print);
		return ;
	}
	pthread_mutex_unlock(&info->protect_flag);
	printf("%lld %d %s\n", time_stat, id, status);
	pthread_mutex_unlock(&info->print);
}

void	eating(t_philo *philo, int first_fork, int second_fork)
{
	pthread_mutex_lock(&philo->info->forks[first_fork]);
	status_print(philo->info, philo->philo_id, "has taken a fork");
	if (philo->info->philo_num == 1)
	{
		my_sleep(philo->info->time_to_die);
		return ;
	}
	pthread_mutex_lock(&philo->info->forks[second_fork]);
	status_print(philo->info, philo->philo_id, "has taken a fork");
	status_print(philo->info, philo->philo_id, "is eating");
	pthread_mutex_lock(&philo->philo_mute);
	gettimeofday(&philo->meal_time, NULL);
	pthread_mutex_unlock(&philo->philo_mute);
	my_sleep(philo->info->time_to_eat);
	pthread_mutex_unlock(&philo->info->forks[second_fork]);
	pthread_mutex_unlock(&philo->info->forks[first_fork]);
	pthread_mutex_lock(&philo->info->protect_eaten);
	philo->meal_count += 1;
	if (philo->meal_count == philo->info->philo_must_eat)
		philo->info->eaten_philo += 1;
	pthread_mutex_unlock(&philo->info->protect_eaten);
}

void	*routine(void *p)
{
	t_philo	*philo;
	int		first_fork;
	int		second_fork;

	philo = (t_philo *)p;
	if (philo->philo_id % 2 == 0)
		usleep(200);
	while (1)
	{
		status_print(philo->info, philo->philo_id, "is thinking");
		usleep(100);
		choose_fork(philo, &first_fork, &second_fork);
		eating(philo, first_fork, second_fork);
		pthread_mutex_lock(&philo->info->protect_flag);
		if (philo->info->exit_flag)
		{
			pthread_mutex_unlock(&philo->info->protect_flag);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->info->protect_flag);
		status_print(philo->info, philo->philo_id, "is sleeping");
		my_sleep(philo->info->time_to_sleep);
	}
}
