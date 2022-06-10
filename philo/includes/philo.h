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

int		main();
void*	routine();

#endif