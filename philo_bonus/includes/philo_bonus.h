/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjasmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:43:05 by wjasmine          #+#    #+#             */
/*   Updated: 2022/06/25 17:02:28 by wjasmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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

typedef struct s_info
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_must_eat;
	int				eaten_philo;
	pid_t 			pid_satiety;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*protect_flag; // TODO remove from init
	sem_t			*all_eaten; // TODO remove from init
	int				exit_flag;
	struct timeval	start_prog;
	struct s_philo	*philo;
}	t_info;

typedef struct s_philo
{
	int				philo_id;
	pid_t 			pid;
	pthread_t		thr;
	t_info			*info;
	struct timeval	meal_time;
	int				meal_count;
	sem_t			*eaten;
//	pthread_mutex_t	philo_mute;
}	t_philo;

int			main(int argc, char *argv[]);
void		routine(t_info *info, int i);
int			ft_atoi_ps(const char *str, int *nbr);
int			error_printf(char *err_msg);
int			init(t_info *info, t_philo **philo, int argc, char *argv[]);
int			parsing_check_argv(t_info *info, int argc, char *argv[]);
int			init_philo_array(t_philo **philo, t_info *info);
int			init_single_philo(t_philo *philo, t_info *info, int i, char *name);
int			init_info(t_info *info);
int			are_you_dead(t_philo *philo);
long long	time_converter(struct timeval *time);
long long	get_time(void);
void		status_print(t_info *info, int id, char *status);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		my_destroy(t_philo *philo, t_info *info);
void		my_sleep(int ms);
void		*philo_monitoring(void *p);
void		wait_kill_clean(t_info *info, int pid);
void		my_sem_clean(t_info *info);
char		*name_generator(char *name);
char		*ft_strcpy(char *dst, const char *src);

#endif