/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:18:21 by athonda           #+#    #+#             */
/*   Updated: 2024/12/31 09:15:11 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdlib.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# define NUM_PHILO 5
# define DEAD 1
# define ALIVE 0

typedef struct s_admin	t_admin;
typedef struct s_philo	t_philo;
typedef enum e_status	t_status;

enum e_status
{
	THINKING,
	EATING,
	SLEEPING,
};

struct s_philo
{
	int				id;
	pid_t			pid;
	long			start;
	long			last_supper;
	pthread_t		pt;
	t_status		status;
	struct timeval	tv;
	int				counter;
	int				full;
	t_admin			*m;
};

struct	s_admin
{
	long			epoch;
	long			start;
	unsigned int	nb_philo;
	unsigned int	departure;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				dead;
	int				max_eat;
	int				used[250];
	sem_t			*stick;
	sem_t			*sem_dead;
	pthread_t		pt_monitor;
	t_philo			*p;
};

void	init_admin(t_admin *m, t_philo *p);
void	init_philo(t_philo *p, int i);
int		init_mutex(t_admin *m);
long	ft_atol(char *str);
int		sleeping(t_admin *m, t_philo *p);
int		thinking(t_admin *m, t_philo *p);
int		eating(t_admin *m, t_philo *p);
int		taking_right(t_philo *p);
int		taking_left(t_philo *p);
int		checking(t_philo *p);
void	*constraint(t_admin *m, t_philo *p);
void	*monitoring(void *arg);
long	get_time(void);
void	wait_all(void);

#endif