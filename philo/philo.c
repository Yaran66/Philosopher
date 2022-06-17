/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:59:45 by wjasmine          #+#    #+#             */
/*   Updated: 2022/06/17 16:33:42 by wjasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "includes/philo.h"

//static void	eaten_philo(t_info *info)
//{
//	if (!info->exit_flag)
//	{
//		pthread_mutex_lock(&info->protect_flag);
//		if (info->eaten_philo == info->philo_num)
//			info->exit_flag = 1;
//		pthread_mutex_unlock(&info->protect_flag);
//	}
//}

void	my_destroy(t_philo *philo, t_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->protect_flag);
	while(i < info->philo_num)
		pthread_mutex_destroy(&info->forks[i++]);
/*	i = 0;
	while(i < info->philo_num)
		pthread_mutex_destroy(&philo[i++].philo_mute);*/
	free(info->forks);
	info->forks = NULL;
	free(philo);
	philo = NULL;
}

int are_you_dead(t_philo *philo)
{
	struct timeval current;
	long long		long_current;
	long long		long_meal_time;

	gettimeofday(&current, NULL);
	long_current = time_converter(&current);
	pthread_mutex_lock(&philo->philo_mute);
	long_meal_time = time_converter(&philo->meal_time);
	pthread_mutex_unlock(&philo->philo_mute);
	return ((long_current - long_meal_time) >= philo->info->time_to_die);
}

static int		philo_monitoring(t_philo *philo, t_info *info)
{
	int i;

	while (1)
	{
		i = 0;
//		eaten_philo(info); //TODO check if everyone eaten
		while(i < info->philo_num)
		{
			if (are_you_dead(philo + i))
			{
				status_print(info, philo[i].philo_id, "died");
//				pthread_mutex_lock(&info->protect_flag);
//				info->exit_flag = 1;
//				pthread_mutex_unlock(&info->protect_flag); // no need done in
//				status_print
				i = 0;
				while (i < info->philo_num)
					pthread_join(philo[i++].thr, NULL); // TODO may be we need
					// to handle retrun from join ???????? X3
				my_destroy(philo, info);
				return (0);
			}
			i++;
		}
		//TODO usleep may be ???????
	}
}

int		main(int argc, char *argv[])
{
	t_info	info;
	t_philo *philo;

	memset(&info, 0, sizeof(info));
	if (argc != 5 && argc != 6)
		return (error_printf("ERROR: wrong argc"));
	if (init(&info, &philo, argc, argv))
	{
		free(info.forks);
		info.forks = NULL;
		return (EXIT_FAILURE);
	}
//	printf("number_of_philosophers %d\n time_to_die %d\n time_to_eat %d\n"
//		   "time_to_sleep %d\n"
//		   "number_of_times_each_philosopher_must_eat %d\n", info.philo_num,
//		   info.time_to_die, info.time_to_eat, info.time_to_sleep, info
//		   .philo_must_eat);
	return (philo_monitoring(philo, &info));
}
