/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:43:05 by wjasmine          #+#    #+#             */
/*   Updated: 2022/06/28 15:48:30 by wjasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "includes/philo_bonus.h"

void	ft_clear_sems(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->philo_count)
	{
		sem_close(info->philos[i].eating_sem);
		i++;
	}
	sem_close(info->forks);
	sem_close(info->print);
}

static int	ft_close_eating_sems(t_info *info)
{
	int		i;
	char	name[11];

	i = 0;
	ft_strcpy(name, "eaten_0000\0");
	while (i < info->philo_count)
	{
		sem_unlink(name);
		i++;
		name_generator(name);
	}
	return (0);
}

void	ft_remove_sems(t_info *info)
{
	ft_clear_sems(info);
	sem_unlink("forks");
	sem_unlink("print");
	ft_close_eating_sems(info);
	free(info->philos);
	info->philos = NULL;
}
