/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 19:44:37 by wjasmine          #+#    #+#             */
/*   Updated: 2022/06/28 19:05:49 by wjasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_bonus.h"

static sem_t	*my_sem_init(const char *name, unsigned int value)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (sem != SEM_FAILED)
		return (sem);
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0644, value));
}

char	*name_generator(char *name)
{
	if (name[9] == '9')
	{
		if (name[8] == '9')
		{
			if (name [7] == '9')
			{
				name[9] = '0';
				name[8] = '0';
				name[7] = '0';
				name[6]++;
				return (name);
			}
			name[9] = '0';
			name[8] = '0';
			name[7]++;
			return (name);
		}
		name[9] = '0';
		name[8]++;
		return (name);
	}
	else
		name[9]++;
	return (name);
}

static int	ft_init_sems(t_info *info)
{
	info->forks = my_sem_init("forks", info->philo_count);
	if (info->forks == SEM_FAILED)
		return (-1);
	info->print = my_sem_init("print", 1);
	if (info->print == SEM_FAILED)
		return (-1);
	return (0);
}

static int	ft_init_eating_sems(t_info *info)
{
	int		i;
	char	name[11];

	i = 0;
	ft_strcpy(name, "eaten_0000\0");
	info->philos = (t_philo *)(malloc(sizeof (t_philo) * info->philo_count));
	if (!info->philos)
		return (1);
	while (i < info->philo_count)
	{
		info->philos[i].eating_times = 0;
		info->philos[i].eating_sem = my_sem_init(name, 0);
		if (info->philos[i].eating_sem == SEM_FAILED)
			return (1);
		i++;
		name_generator(name);
	}
	return (0);
}

int	ft_init_argc(t_info *info, int argc, char *argv[])
{
	if (argc >= 5 && argc <= 6)
	{
		if (ft_atoi(argv[1], &info->philo_count) || \
			ft_atoi(argv[2], &info->time_to_die) || \
			ft_atoi(argv[3], &info->time_to_eat) || \
			ft_atoi(argv[4], &info->time_to_sleep))
			return (error_printf("ERROR: wrong type of argv,parser error"));
		info->c_eating_times = -1;
		gettimeofday(&info->program_start_time, 0);
		if (ft_init_eating_sems(info))
			return (1);
		if (ft_init_sems(info))
			return (1);
		if (argc == 6)
			return (ft_atoi(argv[5], &info->c_eating_times));
		return (0);
	}
	return (error_printf("ERROR: wrong argc"));
}
