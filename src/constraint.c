/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constraint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:41:53 by athonda           #+#    #+#             */
/*   Updated: 2024/12/11 21:56:42 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	taking(t_philo *p)
{
	long	now;
	long	time;

	now = get_time();
	time = now - p->m->start;
	printf("%ld %d has taken a fork\n", time, p->id);
}

void	eating(t_philo *p)
{
	long	now;
	long	time;

	now = get_time();
	time = now - p->m->start;
	printf("%ld %d is eating\n", time, p->id);
	p->last_supper = now;
	p->status = EATING;
	p->counter++;
	usleep(p->m->time_eat * 1000);
}

void	thinking(t_philo *p)
{
	long	now;
	long	time;

	now = get_time();
	time = now - p->m->start;
	printf("%ld %d is thinking\n", time, p->id);
	p->status = THINKING;
}

void	sleeping(t_philo *p)
{
	long	now;
	long	time;

	now = get_time();
	time = now - p->m->start;
	printf("%ld %d is sleeping\n", time, p->id);
	p->status = SLEEPING;
	usleep(p->m->time_sleep * 1000);
}

void	found_dead(t_philo *p)
{
	long	now;
	long	time;

	now = get_time();
	time = now - p->m->start;
	printf("%ld %d found dead\n", time, p->id);
}

/**
 * @fn void *constraint(void *arg)
 * @brief environment constraint as start routine
 * @param[in] arg: struct for object constants
 * @param[out] void * basically NULL
 * @return NULL
 */

void	*constraint(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	p->last_supper = p->m->start;
	while (1)
	{
		if (p->id % 2 == 0)
			usleep(100);
		if (p->status != THINKING)
			thinking(p);
		if (pthread_mutex_lock(&p->m->stick[p->id - 1]) == 0)
		{
			taking(p);
			if (pthread_mutex_lock(&p->m->stick[p->id % p->m->nb_philo]) == 0)
			{
				taking(p);
				eating(p);
				pthread_mutex_unlock(&p->m->stick[p->id % p->m->nb_philo]);
			}
			pthread_mutex_unlock(&p->m->stick[p->id - 1]);
		}
		if (p->status == EATING)
			sleeping(p);
		if (p->m->dead == 1)
		{
			found_dead(p);
			return (NULL);
		}
	}
	return (NULL);
}