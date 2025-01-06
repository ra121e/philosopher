/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 20:20:35 by athonda           #+#    #+#             */
/*   Updated: 2025/01/06 10:20:32 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

int	dying(t_admin *m)
{
	long	now;
	long	time;
	long	elapse_time;

	sem_wait(m->sem_print);
	now = get_time();
	sem_wait(m->sem_time);
	if (m->p->last_supper == 0)
		elapse_time = now - m->start;
	else
		elapse_time = now - m->p->last_supper;
	time = now - m->start;
	sem_post(m->sem_time);
	if (elapse_time > m->time_die)
	{
		printf("%ld %d died\n", time, m->p->id);
		m->dead = DEAD;
		sem_post(m->sem_dead);
		return (DEAD);
	}
	sem_post(m->sem_print);
	return (0);
}

int	checking_die(t_admin *m)
{
	unsigned int	nb_eating;

	nb_eating = 0;
	if (dying(m) == 1)
		return (DEAD);
	nb_eating++;
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
		if (checking_die(m) == 1)
			return (NULL);
	}
}

void	*checking(void *arg)
{
	unsigned int	i;
	t_admin			*m;

	m = (t_admin *)arg;
	i = 0;
	while (i < m->max_eat * m->nb_philo)
	{
		sem_wait(m->sem_finish);
		if (m->dead == 1)
		{
			sem_post(m->sem_finish);
			return (NULL);
		}
		else
		{
			sem_post(m->sem_finish);
			sem_wait(m->sem_count);
			i++;
		}
	}
	sem_post(m->sem_dead);
	return (NULL);
}
