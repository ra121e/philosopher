/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:18:21 by athonda           #+#    #+#             */
/*   Updated: 2025/01/04 14:12:19 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H

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
	sem_t			*sem_print;
	sem_t			*sem_count;
	sem_t			*sem_time;
	pthread_t		pt_monitor;
	t_philo			*p;
};

void	init_admin(t_admin *m, t_philo *p);
void	init_philo(t_philo *p, int i);
int		init_mutex(t_admin *m);
void	error_exit(char *str);
long	ft_atol(char *str);
int		sleeping(t_admin *m, t_philo *p);
int		thinking(t_admin *m, t_philo *p);
int		eating(t_admin *m, t_philo *p);
int		taking(t_admin *m, t_philo *p);
void	*checking(void *arg);
void	*motion(t_admin *m, t_philo *p);
void	*monitoring(void *arg);
long	get_time(void);
void	wait_all(void);
void	clean_semaphore(t_admin *m);

#endif
