/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminating_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 14:02:49 by athonda           #+#    #+#             */
/*   Updated: 2025/01/02 14:47:28 by athonda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	*checking_dead(void *arg)
{
	unsigned int	i;
	t_admin			*m;

	m = (t_admin *)arg;
	sem_wait(m->sem_dead);
	i = -1;
	while (++i < m->nb_philo)
	{
		printf("m->p[i] be killed: %d\n", m->p[i].pid);
		kill(m->p[i].pid, SIGKILL);
	}
	return (NULL);
}

void	*checking_full(void *arg)
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
