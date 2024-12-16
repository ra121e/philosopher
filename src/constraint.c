/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constraint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:41:53 by athonda           #+#    #+#             */
/*   Updated: 2024/12/16 16:43:14 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	dining(t_philo *p)
{
	if (pthread_mutex_lock(&p->m->stick[p->id - 1]) == 0)
	{
		if (p->m->nb_philo == 1)
		{
			taking_left(p);
			usleep(p->m->time_die);
			return (1);
		}
		if (p->m->dead != 1)
			taking_left(p);
		if (pthread_mutex_lock(&p->m->stick[p->id % p->m->nb_philo]) == 0)
		{
			if (p->m->dead != 1)
				taking_right(p);
			if (p->m->dead != 1)
				eating(p);
			pthread_mutex_unlock(&p->m->stick[p->id % p->m->nb_philo]);
		}
		pthread_mutex_unlock(&p->m->stick[p->id - 1]);
	}
	return (0);
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
		usleep(5000);
	while (1)
	{
		if (p->status != THINKING && p->m->dead != 1)
			thinking(p);
		if (p->m->dead != 1)
			if (dining(p) == 1)
				return (NULL);
		if (p->status == EATING && p->m->dead != 1 && p->full != 1)
			sleeping(p);
		if (p->m->dead == 1 || p->full == 1)
			return (NULL);
	}
	return (NULL);
}
