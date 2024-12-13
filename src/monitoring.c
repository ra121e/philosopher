/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 20:20:35 by athonda           #+#    #+#             */
/*   Updated: 2024/12/13 19:14:55 by athonda          ###   ########.fr       */
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
				printf("%ld %d died\n", time, philo->id);
				m->dead = 1;
				return (NULL);
			}
		}
	}
}