/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 14:25:25 by wjasmine          #+#    #+#             */
/*   Updated: 2022/06/11 14:25:30 by wjasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "includes/philo.h"


void	eating(t_philo *philo,int first_fork,int second_fork)
{
	pthread_mutex_lock(&philo->info->forks[first_fork]);
	status_print(philo->info, philo->philo_id, "has taken a fork");
	if (philo->info->philo_num == 1)
	{
		usleep(philo->info->time_to_die * 1000); // go to sleep until you dead
		pthread_mutex_unlock(&philo->info->forks[first_fork]);
		return;
	}
	pthread_mutex_lock(&philo->info->forks[second_fork]);
	status_print(philo->info, philo->philo_id, "has taken a fork");
	pthread_mutex_lock(&philo->philo_mute);
	gettimeofday(&philo->meal_time, NULL);
	pthread_mutex_unlock(&philo->philo_mute);
	status_print(philo->info, philo->philo_id, "is eating");
	usleep(philo->info->time_to_eat); // TODO my_sleep
	pthread_mutex_unlock(&philo->info->forks[second_fork]);
	pthread_mutex_unlock(&philo->info->forks[first_fork]);
}

void	*routine(void *p)
{
	t_philo	*philo;
	int 	first_fork;
	int 	second_fork;

	philo = (t_philo *)p;
	if (philo->philo_id % 2 != 0)
		usleep(300);
	status_print(philo->info, philo->philo_id, "is thinking");
	while(1)
	{
		if (philo->philo_id == 1)
		{
			first_fork = 0;
			second_fork = philo->info->philo_num - 1;
		}
		else
		{
			first_fork = philo->philo_id - 2;
			second_fork = philo->philo_id - 1;
		}
		eating(philo, first_fork, second_fork);
		status_print(philo->info, philo->philo_id, "is sleeping");
		usleep(philo->info->time_to_sleep*1000); // TODO my_sleep
		status_print(philo->info, philo->philo_id, "is thinking");
		if(philo->info->exit_flag)
			return (0);
		usleep(200);// TODO usleep
	}
}