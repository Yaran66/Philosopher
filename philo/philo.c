/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:59:45 by wjasmine          #+#    #+#             */
/*   Updated: 2022/06/10 17:59:57 by wjasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "includes/philo.h"

//void*	routine()
//{
//	return(0); //TODO lock
//}



int are_you_dead(t_philo *philo)
{
	struct timeval current;
	long long		long_current;
	long long		long_meal_time;

	long_current = time_converter(gettimeofday(&current, NULL));
	long_meal_time = time_converter(&philo->meal_time);
	return ((long_current - long_meal_time) >= philo->info->time_to_die);
}

static int		philo_monitoring(t_philo *philo, t_info *info)
{
	int i;

	i = 0;
	while (1)
	{
		while(i < info->philo_num)
		{
			if (are_you_dead(philo + i))
			{
				// TODO print i philo dies
				info->exit_flag = 1; // TODO mutex protect_flag + lock/unlock
				// TODO join all
				// TODO destroy forks & philo mutexes
				return (0);
			}
			i++;
		}
		i = 0;
	}
}

int		main(int argc, char *argv[])
{
	t_info	info;
	t_philo *philo;

	memset(&info, 0, sizeof(info));
	if (argc != 5 && argc != 6)
		return (error_printf("ERROR: wrong argc"));
	if (init(&info, philo, argc, argv))
	{
		free(info.forks);
		info.forks = NULL;
		return (EXIT_FAILURE);
	}
	printf("number_of_philosophers %d\n time_to_die %d\n time_to_eat %d\n"
		   "time_to_sleep %d\n"
		   "number_of_times_each_philosopher_must_eat %d\n", info.philo_num,
		   info.time_to_die, info.time_to_eat, info.time_to_sleep, info
		   .philo_must_eat);
	return (philo_monitoring(philo, &info));
}

//int main()
//{
//	pthread_t th[20];
//	int	i;
//	pthread_mutex_init(&mutex, NULL);
//	for (i = 0; i < 20; i++)
//	{
//		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
//		{
//			perror("Failed to create thread");
//			return 1;
//		}
//		printf("thread %d has started\n", i);
//	}
//	for (i = 0; i < 20; i++)
//	{
//		if (pthread_join(th[i], NULL) != 0){
//			return 2;
//		}
//		printf("thread %d has finished execution\n", i);
//	}
//	pthread_mutex_destroy(&mutex);
//	printf("Number of emails %d\n", mails);
//	return (0);
//}
