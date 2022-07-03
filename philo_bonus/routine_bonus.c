/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:59:45 by wjasmine          #+#    #+#             */
/*   Updated: 2022/06/28 19:24:23 by wjasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_bonus.h"

void	*philo_observe(void *data)
{
	t_timeval	current_time;
	t_info		*info;

	info = data;
	while (1)
	{
		gettimeofday(&current_time, 0);
		if ((current_time.tv_sec \
			- info->philos[info->philo_count].last_eat_time.tv_sec) * 1000
			+ (current_time.tv_usec \
				- info->philos[info->philo_count].last_eat_time.tv_usec) / 1000
			>= info->time_to_die)
		{
			ft_print(info, info->philo_count, DYING);
			exit(1);
		}
		usleep(500);
	}
}

int	routine(t_info *info, int philo_num)
{
	info->philo_count = philo_num;
	gettimeofday(&info->philos[philo_num].last_eat_time, 0);
	pthread_create(&info->add_thread, 0, philo_observe, info);
	pthread_detach(info->add_thread);
	while (1)
	{
		sem_wait(info->forks);
		ft_print(info, philo_num, TAKING_FORK);
		sem_wait(info->forks);
		ft_print(info, philo_num, TAKING_FORK);
		ft_print(info, philo_num, EATING);
		my_sleep(info->time_to_eat);
		sem_post(info->philos[philo_num].eating_sem);
		gettimeofday(&info->philos[philo_num].last_eat_time, 0);
		sem_post(info->forks);
		sem_post(info->forks);
		ft_print(info, philo_num, SLEEPING);
		my_sleep(info->time_to_sleep);
		ft_print(info, philo_num, THINKING);
	}
}
