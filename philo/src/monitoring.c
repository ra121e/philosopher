/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 20:20:35 by athonda           #+#    #+#             */
/*   Updated: 2025/01/04 13:42:20 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	dying(t_admin *m, unsigned int i)
{
	long	now;
	long	time;
	long	elapse_time;

	pthread_mutex_lock(&m->mutex_print);
	{
		now = get_time();
		pthread_mutex_lock(&m->mutex_time);
		elapse_time = now - m->p[i].last_supper;
		pthread_mutex_unlock(&m->mutex_time);
		time = now - m->start;
		if (elapse_time > m->time_die)
		{
			printf("%ld %d died\n", time, m->p[i].id);
			pthread_mutex_lock(&m->mutex_dead);
			m->dead = DEAD;
			pthread_mutex_unlock(&m->mutex_dead);
			return (pthread_mutex_unlock(&m->mutex_print), DEAD);
		}
	}
	pthread_mutex_unlock(&m->mutex_print);
	return (0);
}

int	checking_die(t_admin *m)
{
	unsigned int	i;
	unsigned int	nb_eating;

	nb_eating = 0;
	i = 0;
	while (++i <= m->nb_philo)
	{
		pthread_mutex_lock(&m->mutex_full);
		if (m->p[i].full != 0)
		{
			pthread_mutex_unlock(&m->mutex_full);
			continue ;
		}
		pthread_mutex_unlock(&m->mutex_full);
		if (dying(m, i) == 1)
			return (DEAD);
		nb_eating++;
	}
	if (nb_eating == 0)
		return (1);
	return (0);
}

/**
 * @fn *monitoring(void *arg)
 * @brief start routine for monitoring thread
 * @param[in]	arg void pointer to general info struct
 * @param[out]	void pointer should be return NULL
 * @note
	- non stop while loop
	- checking loop for all philo struct one by one
	- calculate elapse time from the last supper with now
	- compare elapse time to time to death from set value
 */

void	*monitoring(void *arg)
{
	t_admin			*m;

	m = (t_admin *)arg;
	while (1)
	{
		pthread_mutex_lock(&m->mutex_start);
		if (m->departure >= m->nb_philo)
		{
			pthread_mutex_unlock(&m->mutex_start);
			break ;
		}
		pthread_mutex_unlock(&m->mutex_start);
	}
	while (1)
	{
		if (checking_die(m) == 1)
			return (NULL);
	}
}
