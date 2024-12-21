/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constraint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:41:53 by athonda           #+#    #+#             */
/*   Updated: 2024/12/21 16:14:46 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file constraints.c
 * @brief condition limits the degrees of freedom of a system
 * @note
 */

#include "philosopher.h"

/**
 * @fn int solo_dining(t_philo *p)
 * @brief in case of object number is one
 */

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

/**
 * @fn int dining_left(t_philo *p)
 * @brief take left stick at first then take right
 */

int	dining_left(t_philo *p)
{
	pthread_mutex_lock(&p->m->stick[p->id - 1]);
	{
		if (taking_left(p))
			return (pthread_mutex_unlock(&p->m->stick[p->id - 1]), 1);
		pthread_mutex_lock(&p->m->stick[p->id % p->m->nb_philo]);
		{
			if (taking_right(p))
			{
				pthread_mutex_unlock(&p->m->stick[p->id % p->m->nb_philo]);
				pthread_mutex_unlock(&p->m->stick[p->id - 1]);
				return (1);
			}
			if (eating(p))
			{
				pthread_mutex_unlock(&p->m->stick[p->id % p->m->nb_philo]);
				pthread_mutex_unlock(&p->m->stick[p->id - 1]);
				return (1);
			}
		}
		pthread_mutex_unlock(&p->m->stick[p->id % p->m->nb_philo]);
	}
	pthread_mutex_unlock(&p->m->stick[p->id - 1]);
	return (0);
}

/**
 * @fn int dining_right(t_philo *p)
 * @brief take right stick at first, then take left
 */

int	dining_right(t_philo *p)
{
	pthread_mutex_lock(&p->m->stick[p->id % p->m->nb_philo]);
	{
		if (taking_right(p))
			return (pthread_mutex_unlock \
			(&p->m->stick[p->id % p->m->nb_philo]), 1);
		pthread_mutex_lock(&p->m->stick[p->id - 1]);
		{
			if (taking_left(p))
			{
				pthread_mutex_unlock(&p->m->stick[p->id - 1]);
				pthread_mutex_unlock(&p->m->stick[p->id % p->m->nb_philo]);
				return (1);
			}
			if (eating(p))
			{
				pthread_mutex_unlock(&p->m->stick[p->id - 1]);
				pthread_mutex_unlock(&p->m->stick[p->id % p->m->nb_philo]);
				return (1);
			}
		}
		pthread_mutex_unlock(&p->m->stick[p->id - 1]);
	}
	pthread_mutex_unlock(&p->m->stick[p->id % p->m->nb_philo]);
	return (0);
}

/**
 * @fn int dining(t_philo *p)
 * @brief strategy to group with different order to take sticks
 */

int	dining(t_philo *p)
{
	if (solo_dining(p) == 1)
		return (pthread_mutex_unlock(&p->m->stick[p->id - 1]), 1);
	if (p->id % 2 == 0)
	{
		if (dining_right(p) == 1)
			return (1);
		return (0);
	}
	else
	{
		if (dining_left(p) == 1)
			return (1);
		return (0);
	}
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
