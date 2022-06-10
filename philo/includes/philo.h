/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:43:05 by wjasmine          #+#    #+#             */
/*   Updated: 2022/05/19 21:20:40 by wjasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h> // usleep, write
#include <string.h> // printf
#include <stdio.h> // memset
#include <stdlib.h> // malloc, free
#include <pthread.h> // pthread_create, etc....
#include <sys/time.h> // gettimeofday
#include <limits.h>

typedef struct	s_info
{
	int 			philo_num;
	int 			time_to_die;
	int 			time_to_eat;
	int				time_to_sleep;
	int				philo_must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	protect_flag;	// TODO initialize mutex
	int				exit_flag;
	struct timeval	start_prog;
}	t_info;

typedef struct	s_philo
{
	int 			philo_id;
	pthread_t		thr;
	t_info			*info;
	struct timeval	meal_time;
	int 			meal_count;
	pthread_mutex_t philo_mute;
}	t_philo;

int		main(int argc, char *argv[]);
void*	routine();
int		init(t_info *info,int argc, char *argv[]);
int		ft_atoi_ps(const char *str, int *nbr);
int		error_printf(char *err_msg);
int		init(t_info *info, t_philo *philo, int argc, char *argv[]);
int		parsing_check_argv(t_info *info, int argc, char *argv[]);
int 	init_philo_array(t_philo *philo, t_info *info);
int		init_single_philo(t_philo *philo, t_info *info, int i);
int 	init_info(t_info *info);
int		are_you_dead(t_philo *philo);
long long	time_converter(struct timeval *time);

#endif