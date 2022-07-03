/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:43:05 by wjasmine          #+#    #+#             */
/*   Updated: 2022/06/28 18:09:55 by wjasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h> // usleep, write
# include <string.h> // printf
# include <stdio.h> // memset
# include <stdlib.h> // malloc, free
# include <pthread.h> // pthread_create, etc....
# include <sys/time.h> // gettimeofday
# include <limits.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <signal.h>

# define EATING 1
# define THINKING 2
# define SLEEPING 3
# define TAKING_FORK 4
# define DYING 5

typedef struct timeval	t_timeval;

typedef struct s_philo
{
	sem_t		*eating_sem;
	pid_t		pid;
	t_timeval	last_eat_time;
	int			eating_times;
}	t_philo;

typedef struct s_info
{
	sem_t		*forks;
	sem_t		*print;
	t_philo		*philos;
	pthread_t	add_thread;
	int			philo_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			c_eating_times;
	t_timeval	program_start_time;
}	t_info;

int		ft_init_argc(t_info *info, int argc, char *argv[]);

char	*ft_strcpy(char *dst, const char *src);
int		ft_atoi(const char *str, int *_res);
int		ft_print(t_info *info, int philo_num, int condition);

void	*eating_observe(void *data);
int		routine(t_info *info, int philo_num);
void	ft_clear_sems(t_info *info);
void	ft_remove_sems(t_info *info);
char	*name_generator(char *name);
int		error_printf(char *err_msg);
void	my_sleep(int ms);

#endif