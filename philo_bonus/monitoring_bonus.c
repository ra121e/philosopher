/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 20:20:35 by athonda           #+#    #+#             */
/*   Updated: 2025/01/01 09:30:49 by athonda          ###   ########.fr       */
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
//		pthread_mutex_lock(&m->mutex_time);
	if (m->p->last_supper == 0)
		elapse_time = now - m->start;
	else
		elapse_time = now - m->p->last_supper;
//		pthread_mutex_unlock(&m->mutex_time);
	time = now - m->start;
	if (elapse_time > m->time_die)
	{
		printf("%ld %d died\n", time, m->p->id);
		m->dead = DEAD;
		sem_post(m->sem_dead);
		return (DEAD);
//			return (pthread_mutex_unlock(&m->mutex_print), DEAD);
	}
	sem_post(m->sem_print);
	return (0);
}

int	checking_die(t_admin *m)
{
//	unsigned int	i;
	unsigned int	nb_eating;

	nb_eating = 0;
//	i = 0;
//	while (++i <= m->nb_philo && m->p[i].full == 0)
	{
//		printf("monitoring: philo %d\n", m->p->id);
		if (dying(m) == 1)
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
//	while (1)
//	{
//		pthread_mutex_lock(&m->mutex_start);
//		if (m->departure >= m->nb_philo)
//		{
//			pthread_mutex_unlock(&m->mutex_start);
//			break ;
//		}
//		pthread_mutex_unlock(&m->mutex_start);
//	}
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
		sem_wait(m->sem_count);
		i++;
	}
	sem_post(m->sem_dead);
	return (NULL);
}