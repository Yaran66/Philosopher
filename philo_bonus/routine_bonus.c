#include "includes/philo_bonus.h"

static void	array_sem_unlink(t_info *info)
{
	int		i;
	char	name[11];

	i = 0;
	ft_strcpy(name, "eaten_0000\0");
	while (i < info->philo_num)
	{
		sem_unlink(name);
		i++;
		name_generator(name);
	}
}

void	my_sem_clean(t_info *info)
{
	int i;

	i = 0;
	while (i < info->philo_num)
	{
		sem_close(info->philo[i].eaten);
		i++;
	}
	sem_close(info->forks);
	sem_unlink("forks");
	sem_close(info->print);
	sem_unlink("print");
	array_sem_unlink(info);
}

void	wait_kill_clean(t_info *info, int pid)
{
	pid_t	done_pid;
	int		i;

	i = 0;
	done_pid = waitpid(-1, 0, 0);
	if(pid)
		kill(pid, SIGTERM);
	while(i < info->philo_num)
	{
		if (info->philo[i].pid != done_pid)
			kill(info->philo[i].pid, SIGTERM);
	}
	my_sem_clean(info);
}

void	status_print(t_info *info, int id, char *status)
{
	long long	time_stat;

	time_stat = get_time() - time_converter(&info->start_prog);
	sem_wait(info->print);
	printf("%lld %d %s\n", time_stat, id, status);
	sem_post(info->print);
}

void	routine(t_info *info, int i)
{
	gettimeofday( &info->philo[i].meal_time, 0);
	pthread_create(&info->philo[i].thr, NULL, philo_monitoring,
				   &info->philo[i]);
	pthread_detach(info->philo[i].thr);
//	if (philo->philo_id % 2 == 0)
//		usleep(200);
	while (1)
	{
		status_print(info, i, "is thinking");
		//usleep(100);
		sem_wait(info->forks);
		status_print(info, i, "has taken a fork");
		sem_wait(info->forks);
		status_print(info, i, "has taken a fork");
		status_print(info, i, "is eating");
		sem_post(info->philo[i].eaten);
		my_sleep(info->time_to_eat);
		gettimeofday(&info->philo[i].meal_time, NULL);
		sem_post(info->forks);
		sem_post(info->forks);
		status_print(info, i, "is sleeping");
		my_sleep(info->time_to_sleep);
	}
}
