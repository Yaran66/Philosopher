//
// Created by Warmonger Jasmine on 6/10/22.
//
#include "includes/philo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 || *s2) && n)
	{
		if (*s1 != *s2)
		{
			return ((unsigned char)*s1 - (unsigned char)*s2);
		}
		s1++;
		s2++;
		n--;
	}
	return (0);
}

void	status_print(t_info *info, int  id, char *status)
{
	long long	time_stat;

	time_stat = get_time() - time_converter(&info->start_prog);
	pthread_mutex_lock(&info->protect_flag);
	pthread_mutex_lock(&info->print);
	if (info->exit_flag)
	{
		pthread_mutex_unlock(&info->protect_flag);
		pthread_mutex_unlock(&info->print);
		return;
	}
	pthread_mutex_unlock(&info->protect_flag);
	printf("%lld %d %s\n", time_stat, id, status);
	if (ft_strncmp(status, "died", 5))
	{
		pthread_mutex_lock(&info->protect_flag);
		info->exit_flag = 1;
		pthread_mutex_unlock(&info->protect_flag);
	}
	pthread_mutex_unlock(&info->print);
}

int	error_printf(char *err_msg)
{
	printf("%s\n", err_msg);
	return (-1);
}

static int	is_space(char c)
{
	int	flag;

	flag = 0;
	if (c == '\t' || c == '\n' || c == '\v')
		flag = 1;
	if (c == '\f' || c == '\r' || c == ' ')
		flag = 1;
	return (flag);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi_ps(const char *str, int *nbr)
{
	int					sign;
	unsigned long long	value;

	sign = 1;
	value = 0;
	while (is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign *= -1;
	}
	if (!ft_isdigit(*str))
		return (-1);
	while (*str >= '0' && *str <= '9' && *str != '\0')
	{
		value = (value * 10) + (*str++ - '0');
		if ((value > INT_MAX && sign == 1)
			|| (value > (unsigned long long)INT_MAX + 1 && sign == -1))
			return (-1);
	}
	if (*str)
		return (-1);
	*nbr = (value * sign);
	return (0);
}
