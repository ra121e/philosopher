/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:18:21 by athonda           #+#    #+#             */
/*   Updated: 2024/12/09 21:18:32 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#define NUM_PHILO 5

typedef struct s_philo
{
	int			id;
	long		start;
	pthread_t	pt;
	struct timeval tv;
	int	counter;
}	t_philo;

typedef struct	s_admin
{
	long			epoch;
	unsigned int	nb_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				dead;
	int				max_eat;
	pthread_mutex_t	mutex;
	pthread_mutex_t	stick[200];
	t_philo			*p;
}	t_admin;

void	init_admin(t_admin *m);
void	init_philo(t_philo *p);
long	ft_atol(char *str);
void	error_exit(char *str);