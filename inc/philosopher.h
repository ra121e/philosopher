/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:18:21 by athonda           #+#    #+#             */
/*   Updated: 2024/12/11 21:02:06 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#define NUM_PHILO 5

typedef struct s_admin t_admin;
typedef struct s_philo t_philo;
typedef enum e_status t_status;

enum e_status
{
	THINKING,
	EATING,
	SLEEPING,
};

struct s_philo
{
	int			id;
	long		start;
	long		last_supper;
	pthread_t	pt;
	t_status	status;
	struct timeval tv;
	int	counter;
	t_admin		*m;
};

struct	s_admin
{
	long			epoch;
	long			start;
	unsigned int	nb_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				dead;
	int				max_eat;
	pthread_t		pt_monitor;
	pthread_mutex_t	mutex;
	pthread_mutex_t	stick[200];
	t_philo			*p;
};

void	init_admin(t_admin *m, t_philo *p);
void	init_philo(t_philo *p, int i, t_admin *m);
int		init_mutex(t_admin *m);
long	ft_atol(char *str);
void	error_exit(char *str);
void	*constraint(void *arg);
void	*monitoring(void *arg);
long	get_time(void);