/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:59:45 by wjasmine          #+#    #+#             */
/*   Updated: 2022/06/28 19:14:58 by wjasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_bonus.h"

static void	ft_wait_and_kill(t_info *info, pid_t observer_pid)
{
	pid_t	died_philo_pid;
	int		i;

	died_philo_pid = waitpid(-1, 0, 0);
	if (observer_pid)
		kill(observer_pid, SIGKILL);
	i = 0;
	while (i < info->philo_count)
	{
		if (info->philos[i].pid != died_philo_pid)
			kill(info->philos[i].pid, SIGKILL);
		i++;
	}
}

static int	ft_is_all_eat_more(t_philo *philos, \
								int philo_count, int eating_times)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		if (philos[i].eating_times < eating_times)
			return (0);
		i++;
	}
	return (1);
}

static void	ft_kill_all(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_count)
	{
		kill(info->philos[i].pid, SIGKILL);
		i++;
	}
}

void	*eating_observe(void *data)
{
	t_info	*info;
	int		i;

	info = data;
	while (1)
	{
		i = 0;
		while (i < info->philo_count)
		{
			sem_wait(info->philos[i].eating_sem);
			info->philos[i].eating_times++;
			if (ft_is_all_eat_more(info->philos, info->philo_count, \
				info->c_eating_times))
			{
				ft_kill_all(info);
				exit(0);
			}
			i++;
		}
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_info	info;
	int		i;
	pid_t	observer_pid;

	memset(&info, 0, sizeof(info));
	if (ft_init_argc(&info, argc, argv))
		return (1);
	i = 0;
	while (i < info.philo_count)
	{
		info.philos[i].pid = fork();
		if (info.philos[i].pid == 0)
			return (routine(&info, i));
		i++;
	}
	observer_pid = 0;
	if (info.c_eating_times != -1)
	{
		observer_pid = fork();
		if (observer_pid == 0)
			eating_observe(&info);
	}
	ft_wait_and_kill(&info, observer_pid);
	ft_remove_sems(&info);
	return (0);
}
