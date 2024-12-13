/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 20:20:35 by athonda           #+#    #+#             */
/*   Updated: 2024/12/13 19:05:45 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*monitoring(void *arg)
{
	t_admin			*m;
	long			now;
	long			time;
	long			elapse_time;
	unsigned int	i;
	t_philo			*philo;

	m = (t_admin *)arg;
	philo = m->p;
	pthread_mutex_lock(&m->mutex);
	pthread_mutex_unlock(&m->mutex);
	usleep(10000);
	while (1)
	{
		i = 0;
		philo = m->p;
		while (++i <= m->nb_philo)
		{
			philo++;
			now = get_time();
			elapse_time = now - philo->last_supper;
			time = now - m->start;
			if (elapse_time > m->time_die)
			{
				printf("%ld %d now by m\n", now, philo->id);
				printf("%ld %d m->start by m\n", m->start, philo->id);
				printf("%ld %d last_supper by m\n", philo->last_supper, philo->id);
				printf("%ld %d elapse_time by m\n", elapse_time, philo->id);
				printf("%ld %d time_die by m\n", m->time_die, philo->id);
				printf("%ld %d died by m\n", time, philo->id);
				m->dead = 1;
				return (NULL);
			}
		}
	}
}