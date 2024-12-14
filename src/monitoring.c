/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 20:20:35 by athonda           #+#    #+#             */
/*   Updated: 2024/12/14 20:19:30 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	checking_philo(t_admin *m)
{
	unsigned int	i;
	t_philo			*philo;
	long			now;
	long			time;
	long			elapse_time;

	philo = m->p;
	i = 0;
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
			return (1);
		}
	}
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
	pthread_mutex_lock(&m->mutex);
	pthread_mutex_unlock(&m->mutex);
	usleep(10000);
	while (1)
	{
		if (checking_philo(m) == 1)
			return (NULL);
	}
}
