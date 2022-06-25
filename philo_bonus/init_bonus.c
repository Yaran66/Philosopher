#include "includes/philo_bonus.h"

static sem_t	*my_sem_init (const char *name, unsigned int value)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (sem != SEM_FAILED)
		return (sem);
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0644, value));
}

int	init_info(t_info *info)
{
	info->forks = my_sem_init("forks", info->philo_num);
	info->print = my_sem_init("print", 1);
	info->protect_flag = my_sem_init("protect_flag", 0);
	info->all_eaten = my_sem_init("protect_eaten", 0);
	if (info->forks == SEM_FAILED || info->print == SEM_FAILED || \
	info->protect_flag == SEM_FAILED || info->all_eaten == SEM_FAILED)
	{
		sem_close(info->forks);
		sem_close(info->print);
		sem_close(info->protect_flag);
		sem_close(info->all_eaten);
		sem_unlink("forks");
		sem_unlink("print");
		sem_unlink("protect_flag");
		sem_unlink("protect_eaten");
		return (-1);
	}
	return (0);
}

int	init_single_philo(t_philo *philo, t_info *info, int i, char *name)
{
	philo->philo_id = i;
	philo->pid		= 0;
	philo->info = info;
	philo->meal_time = info->start_prog;
	philo->meal_count = 0;
	philo->eaten = my_sem_init(name, 0);
	if (philo->eaten == SEM_FAILED)
		return (-1);
	return (0);
}

char *name_generator(char *name)
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
char	*ft_strcpy(char *dst, const char *src)
{
	char	*res;

	res = dst;
	while (*src)
	{
		*dst = *src;
		dst++;
		src++;
	}
	return (res);
}

int	init_philo_array(t_philo **philo, t_info *info)
{
	int		i;
	char	name[11];

	i = 0;
	ft_strcpy(name, "eaten_0000\0");
	*philo = (t_philo *)(malloc(sizeof (t_philo) * info->philo_num));
	if (!*philo)
		return (-1);
	while (i < info->philo_num)
	{
		//sem_unlink(name);
		if (init_single_philo(*philo + i, info, i + 1, name) == -1)
		{
			free(*philo);//TODO while () to sem_close + sem_unlink separate
			// function with number of philo we stack and clean them
			*philo = NULL;
			return (-1);
		}
		i++;
		name_generator(name);
		//printf("%s\n", name);
	}
	return (0);
}

int	parsing_check_argv(t_info *info, int argc, char *argv[])
{
	if (ft_atoi_ps(argv[1], &info->philo_num) == -1 || \
		ft_atoi_ps(argv[2], &info->time_to_die) == -1 || \
		ft_atoi_ps(argv[3], &info->time_to_eat) == -1 || \
		ft_atoi_ps(argv[4], &info->time_to_sleep) == -1 || \
		(argc == 6 && ft_atoi_ps(argv[5], &info->philo_must_eat) == -1))
		return (error_printf("ERROR: wrong type of arguments, parser error"));
	if (info->philo_num <= 0)
		return (error_printf("ERROR: wrong num of philosophers"));
	if (info->time_to_die < 0)
		return (error_printf("ERROR: wrong time to die"));
	if (info->time_to_eat < 0)
		return (error_printf("ERROR: wrong time to eat"));
	if (info->time_to_sleep < 0)
		return (error_printf("ERROR: wrong time to sleep"));
	if (argc == 6 && info->philo_must_eat <= 0)
		return (error_printf("ERROR: wrong num of times each philo must eat"));
	return (0);
}

int	init(t_info *info, t_philo **philo, int argc, char *argv[])
{
	gettimeofday(&info->start_prog, NULL);
	info->exit_flag = 0;
	if ((parsing_check_argv(info, argc, argv) == -1) || \
			(init_info(info) == -1) || \
			(init_philo_array(philo, info) == -1))
		return (-1);
	return (0);
}
