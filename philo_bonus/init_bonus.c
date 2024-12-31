/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:01:19 by athonda           #+#    #+#             */
/*   Updated: 2024/12/31 17:34:33 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

/**
 * @fn init_mutex(t_admin *m)
 * @brief initialize mutex
 * @param[in]	m pointer to general info struct
 * @param[out]	int
 * @note just use pthread_mutex_init()
 */

/*
int	init_mutex(t_admin *m)
{
	unsigned int	i;
	int				retval;

	i = 0;
	while (i <= m->nb_philo)
	{
		retval = pthread_mutex_init(&m->stick[i], NULL);
		if (retval != 0)
			return (1);
		i++;
	}
	return (0);
}
*/

/**
 * @fn init_admin(t_admin *m, t_philo *p)
 * @brief initialize admin struct
 * @param[in]	m pointer to general info struct
 * @param[in]	p pointer to philo struct array
 *
 */

void	init_admin(t_admin *m, t_philo *p)
{
	m->epoch = 0;
	m->start = 0;
//	m->nb_philo = 0;
//	m->time_die = 0;
//	m->time_eat = 0;
//	m->time_sleep = 0;
	m->dead = 0;
//	m->max_eat = 0;
	m->p = p;
	sem_unlink("/chopstick");
	sem_unlink("/sem_dead");
	sem_unlink("/sem_print");
	sem_unlink("/sem_count");
	m->stick = sem_open("/chopstick", O_CREAT | O_EXCL, 0644, m->nb_philo);
	if (m->stick == SEM_FAILED)
		perror("sem_open error");
	m->sem_dead = sem_open("/sem_dead", O_CREAT | O_EXCL, 0644, 0);
	if (m->sem_dead == SEM_FAILED)
		perror("sem_open error");
	m->sem_print = sem_open("/sem_print", O_CREAT | O_EXCL, 0644, 1);
	if (m->sem_print == SEM_FAILED)
		perror("sem_open error");
	m->sem_count = sem_open("/sem_count", O_CREAT | O_EXCL, 0644, 0);
	if (m->sem_count == SEM_FAILED)
		perror("sem_open error");
}

/**
 * @fn init_philo(t_philo *p, int i, t_admin *m)
 * @brief initialize philo struct array
 * @param[in]	p pointer to philo array
 * @param[in]	i index num of philo array
 * @param[in]	m pointer to general info struct
 * @note
 */


void	init_philo(t_philo *p, int i)
{
	p->id = i;
	p->start = 0;
	p->last_supper = 0;
	p->pt = 0;
	p->status = 0;
	p->tv.tv_sec = 0;
	p->tv.tv_usec = 0;
	p->counter = 0;
	p->full = 0;
}
