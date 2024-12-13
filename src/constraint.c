/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constraint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:41:53 by athonda           #+#    #+#             */
/*   Updated: 2024/12/13 18:49:37 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	taking_left(t_philo *p)
{
	long	now;
	long	time;

	p->m->used[p->id - 1] = 1;
	now = get_time();
	time = now - p->m->start;
	printf("%ld %d has taken a fork\n", time, p->id);
}

void	taking_right(t_philo *p)
{
	long	now;
	long	time;

	p->m->used[p->id % p->m->nb_philo] = 1;
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
	if (p->id % 2 == 0)
		usleep(7000);
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
	pthread_mutex_lock(&p->m->mutex);
	p->last_supper = p->m->start;
	pthread_mutex_unlock(&p->m->mutex);
	printf("%ld %d m.start by philo\n", p->m->start, p->id);
	printf("%ld %d last_supper by philo\n", p->last_supper, p->id);
	if (p->id % 2 == 0)
		usleep(7000);
	while (1)
	{
		if (p->status != THINKING)
			thinking(p);
		if (p->m->used[p->id - 1] == 0 && p->m->used[p->id % p->m->nb_philo] == 0)
		{
			p->m->used[p->id - 1] = 1;
			p->m->used[p->id % p->m->nb_philo] = 1;
			if (pthread_mutex_lock(&p->m->stick[p->id - 1]) == 0)
			{
				taking_left(p);
				if (pthread_mutex_lock(&p->m->stick[p->id % p->m->nb_philo]) == 0)
				{
					taking_right(p);
					eating(p);
					pthread_mutex_unlock(&p->m->stick[p->id % p->m->nb_philo]);
					p->m->used[p->id % p->m->nb_philo] = 0;
				}
				pthread_mutex_unlock(&p->m->stick[p->id - 1]);
				p->m->used[p->id - 1] = 0;
			}
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