/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constraint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:41:53 by athonda           #+#    #+#             */
/*   Updated: 2024/12/19 15:17:25 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	solo_dining(t_philo *p)
{
	if (p->m->nb_philo == 1)
	{
		taking_left(p);
		usleep(p->m->time_die);
		return (1);
	}
	return (0);
}

int	dining(t_philo *p)
{
	pthread_mutex_lock(&p->m->stick[p->id - 1]);
	{
		if (solo_dining(p) == 1)
			return (pthread_mutex_unlock(&p->m->stick[p->id - 1]), 1);
		if (taking_left(p))
			return (pthread_mutex_unlock(&p->m->stick[p->id - 1]), 1);
		pthread_mutex_lock(&p->m->stick[p->id % p->m->nb_philo]);
		{
			if (taking_right(p))
			{
				pthread_mutex_unlock(&p->m->stick[p->id % p->m->nb_philo]);
				return (pthread_mutex_unlock(&p->m->stick[p->id - 1]), 1);
			}
			if (eating(p))
			{
				pthread_mutex_unlock(&p->m->stick[p->id % p->m->nb_philo]);
				return (pthread_mutex_unlock(&p->m->stick[p->id - 1]), 1);
			}
		}
		pthread_mutex_unlock(&p->m->stick[p->id % p->m->nb_philo]);
	}
	pthread_mutex_unlock(&p->m->stick[p->id - 1]);
	return (0);
}

int	checking(t_philo *p)
{
	pthread_mutex_lock(&p->m->mutex_dead);
	if (p->m->dead == DEAD)
	{
		pthread_mutex_unlock(&p->m->mutex_dead);
		return (DEAD);
	}
	pthread_mutex_unlock(&p->m->mutex_dead);
	return (ALIVE);
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
	pthread_mutex_lock(&p->m->mutex_start);
	p->last_supper = p->m->start;
	pthread_mutex_unlock(&p->m->mutex_start);
	if (p->id % 2 == 0)
		usleep(60000);
	while (1)
	{
		if (thinking(p) == 1)
			return (NULL);
		if (dining(p) == 1)
			return (NULL);
		if (sleeping(p) == 1)
			return (NULL);
		if (p->full == 1)
			return (NULL);
	}
	return (NULL);
}
