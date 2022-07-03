/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:59:45 by wjasmine          #+#    #+#             */
/*   Updated: 2022/06/28 20:06:19 by wjasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "includes/philo.h"

static int	eaten_philo(t_info *info)
{
	pthread_mutex_lock(&info->protect_eaten);
	if (info->eaten_philo == info->philo_num)
	{
		pthread_mutex_unlock(&info->protect_eaten);
		return (1);
	}
	pthread_mutex_unlock(&info->protect_eaten);
	return (0);
}

void	my_destroy(t_philo *philo, t_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->protect_flag);
	pthread_mutex_destroy(&info->protect_eaten);
	while (i < info->philo_num)
		pthread_mutex_destroy(&info->forks[i++]);
	free(info->forks);
	info->forks = NULL;
	free(philo);
	philo = NULL;
}

int	are_you_dead(t_philo *philo)
{
	struct timeval	current;
	long long		long_current;
	long long		long_meal_time;

	gettimeofday(&current, NULL);
	long_current = time_converter(&current);
	pthread_mutex_lock(&philo->philo_mute);
	long_meal_time = time_converter(&philo->meal_time);
	pthread_mutex_unlock(&philo->philo_mute);
	return ((long_current - long_meal_time) >= philo->info->time_to_die);
}

static int	philo_monitoring(t_philo *philo, t_info *info)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < info->philo_num)
		{
			if (are_you_dead(philo + i) || eaten_philo(info))
			{
				pthread_mutex_lock(&info->protect_flag);
				info->exit_flag = 1;
				pthread_mutex_unlock(&info->protect_flag);
				if (are_you_dead(philo + i))
					status_print(info, philo[i].philo_id, "died");
				i = 0;
				while (i < info->philo_num)
					pthread_join(philo[i++].thr, NULL);
				my_destroy(philo, info);
				return (0);
			}
			i++;
		}
		usleep(500);
	}
}

int	main(int argc, char *argv[])
{
	t_info	info;
	t_philo	*philo;

	memset(&info, 0, sizeof(info));
	if (argc != 5 && argc != 6)
		return (error_printf("ERROR: wrong argc"));
	if (init(&info, &philo, argc, argv))
	{
		free(info.forks);
		info.forks = NULL;
		return (1);
	}
	return (philo_monitoring(philo, &info));
}
