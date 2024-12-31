/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constraint_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:41:53 by athonda           #+#    #+#             */
/*   Updated: 2024/12/31 16:05:28 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file constraints.c
 * @brief condition limits the degrees of freedom of a system
 * @note
 */

#include "philosopher_bonus.h"

/**
 * @fn int solo_dining(t_philo *p)
 * @brief in case of object number is one
 */

int	solo_dining(t_admin *m, t_philo *p)
{
	if (m->nb_philo == 1)
	{
		taking(m, p);
		usleep(m->time_die);
		return (1);
	}
	return (0);
}


/**
 * @fn int dining_left(t_philo *p)
 * @brief take left stick at first then take right
 */

/*
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
*/

/**
 * @fn int dining_right(t_philo *p)
 * @brief take right stick at first, then take left
 */
/*
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
*/

/**
 * @fn int dining(t_philo *p)
 * @brief strategy to group with different order to take sticks
 */
/*
int	dining(t_admin *m, t_philo *p)
{
	if (solo_dining(p) == 1)
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
*/

/**
 * @fn void *constraint(void *arg)
 * @brief environment constraint as start routine
 * @param[in] arg: struct for object constants
 * @param[out] void * basically NULL
 * @return NULL
 */

void	*constraint(t_admin *m, t_philo *p)
{
	p->last_supper = m->start;
	if (solo_dining(m, p) == 1)
		sem_wait(m->stick);
//	if (p->id % 2 == 0)
//		usleep(5000);
	while (1)
	{
		if (thinking(m, p) == 1)
			return (NULL);
		if (eating(m, p) == 1)
			break ;
		if (sleeping(m, p) == 1)
			return (NULL);
		if (p->full == 1)
			exit(1);
	}
	exit(1);
}
